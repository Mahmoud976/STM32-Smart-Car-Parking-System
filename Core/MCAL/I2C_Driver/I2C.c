#include "I2C.h"


/*
 * I2C pinout                 Configuration               GPIO configuration
 *
 * I2Cx_SCL                   I2C clock                   Alternate function open drain
 *
 * I2Cx_SDA                   I2C Data I/O                Alternate function open drain
 *
 *PB7 (SDA) and PB6 (SCL), while the secondary interface, I2C2, uses PB11 (SDA) and PB10 (SCL)
 */

static void I2C_pin_cfg(I2C_Handle_t *hi2c)
{
	GPIO_Config_Pin_t pin_cfg;
	if(hi2c->Instance==I2C1)
	{
		pin_cfg.PORTx=PORTB;
		pin_cfg.Pin_Number=GPIO_PIN6;
		pin_cfg.mode=GPIO_MODE_Output_AF_OD;
		GPIO_InitPin(&pin_cfg);
		pin_cfg.Pin_Number=GPIO_PIN7;
		GPIO_InitPin(&pin_cfg);
		I2C_Enable(hi2c->Instance);

	}
	else if(hi2c->Instance==I2C2)
	{
		pin_cfg.PORTx=PORTB;
		pin_cfg.Pin_Number=GPIO_PIN10;
		pin_cfg.mode=GPIO_MODE_Output_AF_OD;
		GPIO_InitPin(&pin_cfg);
		pin_cfg.Pin_Number=GPIO_PIN11;
		GPIO_InitPin(&pin_cfg);
		I2C_Enable(hi2c->Instance);
	}
	else
	{
	 /*INVALID PORT*/
	}
}

// ---------- Handle Normal Event ----------
static void I2C_HandleEvent(I2C_Handle_t *hi2c, uint32_t event)
{
    hi2c->State = I2C_STATE_READY;
    hi2c->Lock  = I2C_UNLOCKED;

    if(hi2c->Config.Callback)
        hi2c->Config.Callback(event);
}

// ---------- Handle Error ----------
static void I2C_HandleError(I2C_Handle_t *hi2c, uint32_t error)
{
    hi2c->State = I2C_STATE_READY;
    hi2c->Lock  = I2C_UNLOCKED;
    hi2c->ErrorCode |= error;

    if(hi2c->Config.ErrorCallback)
        hi2c->Config.ErrorCallback(error);

    // Clear error flags in hardware
    hi2c->Instance->SR1 &= ~(I2C_SR1_BERR | I2C_SR1_ARLO | I2C_SR1_AF | I2C_SR1_OVR | I2C_SR1_TIMEOUT);
}

/*=========================================================
                DEFAULT CONFIG
=========================================================*/

/**
 * @brief  Returns the default I2C configuration
 * @retval I2C_Config_t: structure with default settings
 */
I2C_Config_t I2C_DefaultConfig(void)
{
    I2C_Config_t config;
    config.ClockSpeed = I2C_SM_100K;
    config.OwnAddress = I2C_OWN_ADDRESS_7BIT(0x52);
    config.ACKControl = I2C_ACK_ENABLE;
    config.AddressingMode = I2C_ADDRESS_7BIT_MODE;
    config.DualAddress = I2C_DUAL_DISABLE;
    config.SecondAddress = 0;
    config.IT_Config = 0;
    config.Callback = I2C_CALLBACK_NULL;
    return config;
}

/*=========================================================
                BUS RECOVERY
=========================================================*/

/**
 * @brief  Tries to recover the I2C bus in case of stuck lines
 * @param  hi2c: pointer to I2C handle
 * @retval None
 */
void I2C_BusRecover(I2C_Handle_t *hi2c)
{
    if(NULL == hi2c) return;

    I2C_Disable(hi2c->Instance);

    GPIO_Config_Pin_t pin_cfg;
    uint16_t scl_pin, sda_pin;

    if(hi2c->Instance == I2C1) { scl_pin = GPIO_PIN6; sda_pin = GPIO_PIN7; pin_cfg.PORTx = PORTB; }
    else if(hi2c->Instance == I2C2) { scl_pin = GPIO_PIN10; sda_pin = GPIO_PIN11; pin_cfg.PORTx = PORTB; }
    else return; // Invalid port

    // Configure pins as push-pull output
    pin_cfg.Pin_Number = scl_pin; pin_cfg.mode = GPIO_MODE_Output_PP; GPIO_InitPin(&pin_cfg);
    pin_cfg.Pin_Number = sda_pin; GPIO_InitPin(&pin_cfg);

    // Generate 9 clock pulses
    for(int i=0; i<9; i++)
    {
        GPIO_WritePin(pin_cfg.PORTx, scl_pin, GPIO_HIGH); delay_us(5);
        GPIO_WritePin(pin_cfg.PORTx, scl_pin, GPIO_LOW);  delay_us(5);
    }

    // Set SDA high
    GPIO_WritePin(pin_cfg.PORTx, sda_pin, GPIO_HIGH);

    // Restore pins to alternate function open-drain
    I2C_pin_cfg(hi2c);
}

/*=========================================================
                PERIPHERAL CLOCK
=========================================================*/

/**
 * @brief  Enable or disable the peripheral clock for a given I2C instance
 * @param  I2Cx: Pointer to the I2C peripheral (I2C1 or I2C2)
 * @param  EnOrDi: Enable or disable the clock
 *         @arg 1: Enable the clock
 *         @arg 0: Disable the clock
 * @retval None
 */
void I2C_PeriClockControl(I2C_TypeDef_t *I2Cx, uint8_t EnOrDi)
{
	if(NULL == I2Cx) return;
	if(I2Cx == I2C1) {(EnOrDi)?RCC_I2C1_CLK_EN():RCC_I2C1_CLK_Reset();}
	else if(I2Cx == I2C2) {(EnOrDi)?RCC_I2C2_CLK_EN():RCC_I2C2_CLK_Reset();}
	else return; // Invalid port
}

/*=========================================================
                INIT & DEINIT
=========================================================*/

/**
 * @brief  Initializes the I2C peripheral
 * @param  hi2c: pointer to I2C handle with configuration
 * @retval I2C_Status_t: status of initialization
 */
I2C_Status_t I2C_Init(I2C_Handle_t *hi2c)
{
	// 1. Check if handle is NULL
    if(NULL==hi2c)
    	return I2C_ERROR_BERR;  // if NULL, return I2C_ERROR_INVALID_PARAM
    else
    {
        // 2. Enable I2C peripheral clock using I2C_PeriClockControl
    	I2C_PeriClockControl(hi2c->Instance,ENABLE);
    	// 3. Initialize GPIO pins for SDA and SCL based on I2C instance
    	I2C_pin_cfg(hi2c);
		// 4. Disable I2C before configuration using I2C_Disable
    	I2C_Disable(hi2c->Instance);
		// 5. Configure CR2 register:
		//    - Set peripheral clock frequency


/*
 * Bits 5:0 FREQ[5:0]: Peripheral clock frequency
 * The FREQ bits must be configured with the APB clock frequency value (I2C peripheral
 * connected to APB). The FREQ field is used by the peripheral to generate data setup and
 * hold times compliant with the I2C specifications. The minimum allowed frequency is 2 MHz,
 * the maximum frequency is limited by the maximum APB frequency and cannot exceed
 * 50 MHz (peripheral intrinsic maximum limit).
 * 0b000000: Not allowed
 * 0b000001: Not allowed
 * 0b000010: 2 MHz
 * ...
 * 0b110010: 50 MHz
 * Higher than 0b101010: Not allowed
 *
 * */
    	uint32_t tempreg = 0;
    	uint32_t PCLK1 =RCC_Get_PCLK1Freq();
    	// Set peripheral clock frequency (CR2 FREQ bits)
    	tempreg |= (PCLK1 / 1000000U) & I2C_CR2_FREQ_Msk;  // APB1_CLOCK in MHz

    	//    - Enable interrupts if required (ITEVTEN, ITBUFEN, ITERREN)
    	if (hi2c->Config.IT_Config & I2C_IT_EVT)    tempreg |= I2C_CR2_ITEVTEN;
    	if (hi2c->Config.IT_Config & I2C_IT_BUF)    tempreg |= I2C_CR2_ITBUFEN;
    	if (hi2c->Config.IT_Config & I2C_IT_ERR)    tempreg |= I2C_CR2_ITERREN;

    	// Write the configured value to CR2 register
    	hi2c->Instance->CR2 = tempreg;


		// 6. Configure CCR register:
		//    - Calculate and set clock control based on ClockSpeed (SM/100kHz or FM/400kHz) CCR = PCLK1 / (2 * ClockSpeed)
    	if(hi2c->Config.ClockSpeed <= I2C_SM_100K) // Standard Mode
    	{
    	    hi2c->Instance->CCR = PCLK1 / (2 * hi2c->Config.ClockSpeed);
    	    hi2c->Instance->CCR &= ~I2C_CCR_FS; // Clear FM bit
    	}
    	else // Fast Mode
    	{
    	    hi2c->Instance->CCR = PCLK1 / (3 * hi2c->Config.ClockSpeed);
    	    hi2c->Instance->CCR |= I2C_CCR_FS; // Set FM bit
    	}

		// 7. Configure TRISE register:
		//    - Set maximum rise time based on ClockSpeed
    	// 7. Configure TRISE register
    	if (hi2c->Config.ClockSpeed <= I2C_SM_100K) // Standard Mode (<=100kHz)
    	{
    	    hi2c->Instance->TRISE = ((PCLK1 / 1000000U) + 1U); // Max rise time = 1000 ns
    	}
    	else // Fast Mode (>100kHz)
    	{
    	    hi2c->Instance->TRISE = (((PCLK1 * 300U) / 1000000000U) + 1U); // Max rise time = 300 ns
    	}



    	// 8. Configure CR1 register

    	// Clear relevant bits first
    	hi2c->Instance->CR1 &= ~(I2C_CR1_ACK | I2C_CR1_POS | I2C_CR1_SWRST);

    	// 8.1 Enable/disable ACK
    	if (hi2c->Config.ACKControl == I2C_ACK_ENABLE)
    	{
    	    hi2c->Instance->CR1 |= I2C_CR1_ACK;
    	}
    	else
    	{
    	    hi2c->Instance->CR1 &= ~I2C_CR1_ACK;
    	}

    	// 8.2 Set addressing mode (7-bit or 10-bit)
    	if (hi2c->Config.AddressingMode == I2C_ADDRESS_7BIT_MODE)
    	{
    	    hi2c->Instance->OAR1 &= ~I2C_ADDRESS_10BIT_MODE; // Clear 10-bit mode bit
    	}
    	else
    	{
    	    hi2c->Instance->OAR1 |= I2C_ADDRESS_10BIT_MODE;  // Set 10-bit mode bit
    	}

    	// 8.3 Configure dual addressing if required
    	if (hi2c->Config.DualAddress == I2C_DUAL_ENABLE)
    	{
    	    hi2c->Instance->OAR2 = I2C_SECOND_ADDRESS_ENABLE(hi2c->Config.SecondAddress);
    	}
    	else
    	{
    	    hi2c->Instance->OAR2 = I2C_SECOND_ADDRESS_DISABLE;
    	}


		// 9. Enable I2C peripheral using I2C_Enable

    	I2C_Enable(hi2c->Instance);
		// 10. Update I2C handle state to I2C_STATE_READY
    	hi2c->State = I2C_STATE_READY;
    	// Also unlock the handle in case it was locked during init
    	hi2c->Lock = I2C_UNLOCKED;

    }
    return I2C_OK;
}

/**
 * @brief  Deinitializes the I2C peripheral
 * @param  hi2c: pointer to I2C handle
 * @retval I2C_Status_t: status of deinitialization
 */
I2C_Status_t I2C_DeInit(I2C_Handle_t *hi2c)
{
    // 1. Check if handle is NULL
    if(hi2c == NULL)
        return I2C_ERROR_BERR;

    // 2. Disable I2C peripheral
    I2C_Disable(hi2c->Instance);

    // 3. Reset I2C peripheral using RCC reset
    if(hi2c->Instance == I2C1)
    {
        RCC_I2C1_CLK_Reset();   // reset I2C1 peripheral
        // deinit GPIO pins (SDA, SCL)
        GPIO_DeInitPin(PORTB,GPIO_PIN6);
        GPIO_DeInitPin(PORTB,GPIO_PIN7);
    }
    else if(hi2c->Instance == I2C2)
    {
        RCC_I2C2_CLK_Reset();   // reset I2C2 peripheral
        // deinit GPIO pins (SDA, SCL)
        GPIO_DeInitPin(PORTB,GPIO_PIN10);
        GPIO_DeInitPin(PORTB,GPIO_PIN11);
    }
    else
    {
        return I2C_ERROR_BERR;  // invalid peripheral
    }




    // 5. Clear I2C handle state and lock
    hi2c->State = I2C_STATE_RESET;
    hi2c->Lock = I2C_UNLOCKED;

    return I2C_OK;
}

/*=========================================================
                MASTER APIs
=========================================================*/

/**
 * @brief  Sends data in master mode (blocking)
 * @param  hi2c: pointer to I2C handle
 * @param  DevAddress: 7/10-bit slave address
 * @param  pData: pointer to data buffer
 * @param  Size: number of bytes to transmit
 * @param  StopMode: I2C_STOP / I2C_NO_STOP / I2C_REPEATED_START
 * @param  Timeout: timeout in ms
 * @retval I2C_Status_t: status of transmission
 */
I2C_Status_t I2C_Master_Transmit(I2C_Handle_t *hi2c,uint16_t DevAddress,const uint8_t *pData,uint16_t Size,I2C_StopMode_t StopMode,uint32_t Timeout)
{
    // 1. Check if the I2C handle, data pointer, or size is valid
	if(NULL == hi2c || NULL == pData) return I2C_ERROR_BERR;  //    - Return error if handle is NULL or Size is 0 or pData is NULL
	else
	{

		 // 2. Check if the I2C peripheral is ready
		uint32_t timeout = Timeout;

		while (hi2c->Instance->SR2 & I2C_SR2_BUSY)
		{
		    if (timeout-- == 0)
		    {
		        return I2C_ERROR_TIMEOUT;
		    }
		}

		// 3. Lock the handle and set state to BUSY_TX
		if (hi2c->Lock == I2C_LOCKED)
		{
		    return I2C_ERROR_BUSY;
		}

		// Lock the handle
		hi2c->Lock = I2C_LOCKED;

		// Update state
		hi2c->State = I2C_STATE_BUSY_TX;

		// Generate START
		I2C_GenerateSTART(hi2c->Instance);

		// Wait until SB flag is set
		timeout = Timeout;
		while (!(hi2c->Instance->SR1 & I2C_SR1_SB))
		{
		    if (timeout-- == 0)
		    {
		    	// - Set state back to READY
				hi2c->State = I2C_STATE_READY;
				// - Unlock the handle so other operations can use it
				hi2c->Lock  = I2C_UNLOCKED;
		        return I2C_ERROR_TIMEOUT;
		    }
		}


		// Send slave address with write bit (LSB = 0)
		hi2c->Instance->DR = (DevAddress & ~0x01U);  // ensure write mode

		// Wait until ADDR flag is set
		timeout = Timeout;
		while (!(hi2c->Instance->SR1 & I2C_SR1_ADDR))
		{
		    if (timeout-- == 0)
		    {
		    	// - Set state back to READY
				hi2c->State = I2C_STATE_READY;
				// - Unlock the handle so other operations can use it
				hi2c->Lock  = I2C_UNLOCKED;
		        return I2C_ERROR_TIMEOUT;
		    }
		}


		// 6. Clear ADDR flag

		// Read SR1 then SR2 to clear ADDR flag
		volatile uint32_t temp;

		// First read SR1
		temp = hi2c->Instance->SR1;

		// Then read SR2
		temp = hi2c->Instance->SR2;

		// Prevent compiler warning (unused variable)
		(void)temp;


		// 7. Transmit data bytes
		while (Size > 0)
		{
		    // Wait until TXE flag is set (data register empty)
		    timeout = Timeout;
		    while (!(hi2c->Instance->SR1 & I2C_SR1_TXE))
		    {
		        if (timeout-- == 0)
		        {
		        	// - Set state back to READY
					hi2c->State = I2C_STATE_READY;
					// - Unlock the handle so other operations can use it
					hi2c->Lock  = I2C_UNLOCKED;
		            return I2C_ERROR_TIMEOUT;
		        }
		    }

		    // Write next byte to DR
		    hi2c->Instance->DR = *pData;

		    // Move to next byte
		    pData++;
		    Size--;
		}


		// 8. Wait for final transmission completion

		// Wait until TXE is set
		timeout = Timeout;
		while (!(hi2c->Instance->SR1 & I2C_SR1_TXE))
		{
		    if (timeout-- == 0)
		    {
		    	// - Set state back to READY
				hi2c->State = I2C_STATE_READY;
				// - Unlock the handle so other operations can use it
				hi2c->Lock  = I2C_UNLOCKED;
		        return I2C_ERROR_TIMEOUT;
		    }
		}

		// Wait until BTF (Byte Transfer Finished) is set
		timeout = Timeout;
		while (!(hi2c->Instance->SR1 & I2C_SR1_BTF))
		{
		    if (timeout-- == 0)
		    {
		    	// - Set state back to READY
				hi2c->State = I2C_STATE_READY;
				// - Unlock the handle so other operations can use it
				hi2c->Lock  = I2C_UNLOCKED;
		        return I2C_ERROR_TIMEOUT;
		    }
		}

		// 9. Generate STOP or REPEATED START

		if (StopMode == I2C_STOP)
		{
		    // Generate STOP condition
		    I2C_GenerateSTOP(hi2c->Instance);
		}
		else if (StopMode == I2C_REPEATED_START)
		{
		    // Generate repeated START
		    I2C_GenerateSTART(hi2c->Instance);
		}
		else
		{
		    // I2C_NO_STOP → do nothing (keep bus active)
		}

		// 10. Unlock and set state to READY
		// - Set state back to READY
		hi2c->State = I2C_STATE_READY;
		// - Unlock the handle so other operations can use it
		hi2c->Lock  = I2C_UNLOCKED;
	}

    // 9. Return I2C_OK
    return I2C_OK;
}

/**
 * @brief  Receives data in master mode (blocking)
 * @param  hi2c: pointer to I2C handle
 * @param  DevAddress: 7/10-bit slave address
 * @param  pData: pointer to buffer to store received data
 * @param  Size: number of bytes to receive
 * @param  StopMode: I2C_STOP / I2C_NO_STOP / I2C_REPEATED_START
 * @param  Timeout: timeout in ms
 * @retval I2C_Status_t: status of reception
 */
I2C_Status_t I2C_Master_Receive(I2C_Handle_t *hi2c,uint16_t DevAddress,uint8_t *pData,uint16_t Size,I2C_StopMode_t StopMode,uint32_t Timeout)
{
	 if (hi2c == NULL || pData == NULL || Size == 0)
	        return I2C_ERROR_BERR;

	    uint32_t timeout;

	    // 1. Wait until I2C bus is free
	    timeout = Timeout;
	    while (hi2c->Instance->SR2 & I2C_SR2_BUSY)
	    {
	        if (timeout-- == 0)
	            return I2C_ERROR_TIMEOUT;
	    }

	    // 2. Lock the handle and set state to BUSY_RX
	    if (hi2c->Lock == I2C_LOCKED) return I2C_ERROR_BUSY;
	    hi2c->Lock = I2C_LOCKED;
	    hi2c->State = I2C_STATE_BUSY_RX;

	    // 3. Generate START condition
	    I2C_GenerateSTART(hi2c->Instance);
	    timeout = Timeout;
	    while (!(hi2c->Instance->SR1 & I2C_SR1_SB))
	    {
	        if (timeout-- == 0)
	        {
	            hi2c->State = I2C_STATE_READY;
	            hi2c->Lock = I2C_UNLOCKED;
	            return I2C_ERROR_TIMEOUT;
	        }
	    }

	    // 4. Send slave address with read bit (LSB = 1)
	    hi2c->Instance->DR = (DevAddress | 0x01U);
	    timeout = Timeout;
	    while (!(hi2c->Instance->SR1 & I2C_SR1_ADDR))
	    {
	        if (timeout-- == 0)
	        {
	            hi2c->State = I2C_STATE_READY;
	            hi2c->Lock = I2C_UNLOCKED;
	            return I2C_ERROR_TIMEOUT;
	        }
	    }

	    // 5. Clear ADDR flag
	    volatile uint32_t temp;
	    temp = hi2c->Instance->SR1;
	    temp = hi2c->Instance->SR2;
	    (void)temp;

	    // 6. Receive data bytes
	    while (Size > 0)
	    {
	        timeout = Timeout;
	        while (!(hi2c->Instance->SR1 & I2C_SR1_RXNE))
	        {
	            if (timeout-- == 0)
	            {
	                hi2c->State = I2C_STATE_READY;
	                hi2c->Lock = I2C_UNLOCKED;
	                return I2C_ERROR_TIMEOUT;
	            }
	        }

	        // Read byte from DR
	        *pData = hi2c->Instance->DR;
	        pData++;
	        Size--;

	        // If last byte, handle STOP / NO_STOP
	        if (Size == 0)
	        {
	            if (StopMode == I2C_STOP)
	            {
	                I2C_GenerateSTOP(hi2c->Instance);
	            }
	            else if (StopMode == I2C_REPEATED_START)
	            {
	                I2C_GenerateSTART(hi2c->Instance);
	            }
	        }
	    }

	    // 7. Unlock and set state to READY
	    hi2c->State = I2C_STATE_READY;
	    hi2c->Lock = I2C_UNLOCKED;

	    return I2C_OK;
}
/*=========================================================
                MASTER INTERRUPT APIs
=========================================================*/

/**
 * @brief  Initiates I2C master transmission in non-blocking interrupt mode
 * @param  hi2c: pointer to I2C handle
 * @param  DevAddress: 7/10-bit slave address
 * @param  pData: pointer to data buffer
 * @param  Size: number of bytes to transmit
 * @retval I2C_Status_t: status of transmission initiation
 */
I2C_Status_t I2C_Master_Transmit_IT(I2C_Handle_t *hi2c,uint16_t DevAddress,const uint8_t *pData,uint16_t Size)
{
	 // 1. Check parameters
	if (hi2c == NULL || pData == NULL || Size == 0)
		return I2C_ERROR_BERR;

	// 2. Check if I2C peripheral is ready
	if (hi2c->State != I2C_STATE_READY)
		return I2C_ERROR_BUSY;

	// 3. Lock the handle and set state to BUSY_TX
	hi2c->Lock = I2C_LOCKED;
	hi2c->State = I2C_STATE_BUSY_TX;

	// 4. Save buffer info in handle
	hi2c->pTxBuffer = pData;
	hi2c->TxLen = Size;
	hi2c->DevAddress = DevAddress;

	// 5. Generate START condition
	I2C_GenerateSTART(hi2c->Instance);

	// 6. Enable I2C event and error interrupts
	hi2c->Instance->CR2 |= (I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN | I2C_CR2_ITERREN);

	// 7. Return immediately; ISR will handle transmission
	return I2C_OK;


}

/**
 * @brief  Initiates I2C master reception in non-blocking interrupt mode
 * @param  hi2c: pointer to I2C handle
 * @param  DevAddress: 7/10-bit slave address
 * @param  pData: pointer to buffer to store received data
 * @param  Size: number of bytes to receive
 * @retval I2C_Status_t: status of reception initiation
 */
I2C_Status_t I2C_Master_Receive_IT(I2C_Handle_t *hi2c,uint16_t DevAddress,uint8_t *pData,uint16_t Size)
{

	if(NULL == hi2c || NULL == pData || Size == 0)
		return I2C_ERROR_BERR;

	// 1. Check if I2C is busy
	if(hi2c->Lock == I2C_LOCKED)
		return I2C_ERROR_BUSY;

	// 2. Lock the handle and update state
	hi2c->Lock  = I2C_LOCKED;
	hi2c->State = I2C_STATE_BUSY_RX;

	// 3. Store buffer and length in handle
	hi2c->pRxBuffer = pData;
	hi2c->RxLen     = Size;
	hi2c->DevAddress= DevAddress;

	// 4. Generate START condition
	I2C_GenerateSTART(hi2c->Instance);

	// 5. Enable I2C event and error interrupts
	hi2c->Instance->CR2 |= I2C_CR2_ITEVTEN;  // Event interrupt
	hi2c->Instance->CR2 |= I2C_CR2_ITERREN;  // Error interrupt

	return I2C_OK;
}

/*=========================================================
                SLAVE APIs
=========================================================*/

/**
 * @brief  Sends data in slave mode
 * @param  hi2c: pointer to I2C handle
 * @param  pData: pointer to data buffer
 * @param  Size: number of bytes to transmit
 * @retval I2C_Status_t: status of transmission
 */
I2C_Status_t I2C_Slave_Transmit(I2C_Handle_t *hi2c,const uint8_t *pData,uint16_t Size)
{
    // 1. Check parameters
    if(hi2c == NULL || pData == NULL || Size == 0)
        return I2C_ERROR_BERR;

    // 2. Lock the handle and set state to BUSY_TX
    if(hi2c->Lock == I2C_LOCKED)
        return I2C_ERROR_BUSY;

    hi2c->Lock = I2C_LOCKED;
    hi2c->State = I2C_STATE_BUSY_TX;
    hi2c->pTxBuffer = pData;
    hi2c->TxLen = Size;

    // 3. Wait for address match from master
    while(!(hi2c->Instance->SR1 & I2C_SR1_ADDR))
    {
        // Blocking wait until master addresses this slave
    }

    // 4. Clear ADDR flag
    volatile uint32_t temp = hi2c->Instance->SR1;
    temp = hi2c->Instance->SR2;
    (void)temp;

    // 5. Transmit data bytes
    while(Size > 0)
    {
        // Wait until TXE (data register empty)
        while(!(hi2c->Instance->SR1 & I2C_SR1_TXE));

        // Send next byte
        hi2c->Instance->DR = *pData;
        pData++;
        Size--;
    }

    // 6. Wait until BTF (Byte Transfer Finished)
    while(!(hi2c->Instance->SR1 & I2C_SR1_BTF));

    // 7. Wait for STOP condition from master
    while(!(hi2c->Instance->SR1 & I2C_SR1_STOPF));

    // 8. Clear STOPF flag by writing CR1
    hi2c->Instance->CR1 |= I2C_CR1_PE;

    // 9. Unlock handle and set state to READY
    hi2c->State = I2C_STATE_READY;
    hi2c->Lock = I2C_UNLOCKED;

    return I2C_OK;

}

/**
 * @brief  Receives data in slave mode
 * @param  hi2c: pointer to I2C handle
 * @param  pData: pointer to buffer to store received data
 * @param  Size: number of bytes to receive
 * @retval I2C_Status_t: status of reception
 */
I2C_Status_t I2C_Slave_Receive(I2C_Handle_t *hi2c, uint8_t *pData,uint16_t Size)
{
    // 1. Check parameters
    if(hi2c == NULL || pData == NULL || Size == 0)
        return I2C_ERROR_BERR;

    // 2. Lock handle and set state to BUSY_RX
    if(hi2c->Lock == I2C_LOCKED)
        return I2C_ERROR_BUSY;

    hi2c->Lock = I2C_LOCKED;
    hi2c->State = I2C_STATE_BUSY_RX;
    hi2c->pRxBuffer = pData;
    hi2c->RxLen = Size;

    // 3. Wait for address match from master
    while(!(hi2c->Instance->SR1 & I2C_SR1_ADDR))
    {
        // Blocking wait until master addresses this slave
    }

    // 4. Clear ADDR flag
    volatile uint32_t temp = hi2c->Instance->SR1;
    temp = hi2c->Instance->SR2;
    (void)temp;

    // 5. Receive data bytes
    while(Size > 0)
    {
        // Wait until RXNE (data register not empty)
        while(!(hi2c->Instance->SR1 & I2C_SR1_RXNE));

        // Read received byte
        *pData = hi2c->Instance->DR;
        pData++;
        Size--;
    }

    // 6. Wait for STOP condition from master
    while(!(hi2c->Instance->SR1 & I2C_SR1_STOPF));

    // 7. Clear STOPF flag by writing CR1
    hi2c->Instance->CR1 |= I2C_CR1_PE;

    // 8. Unlock handle and set state to READY
    hi2c->State = I2C_STATE_READY;
    hi2c->Lock = I2C_UNLOCKED;

    return I2C_OK;
}
/**
 * @brief  Transmit data as I2C slave (interrupt mode)
 * @param  hi2c: pointer to I2C handle
 * @param  pData: pointer to data buffer
 * @param  Size: number of bytes to send
 * @retval I2C_Status_t: status of transmission
 */
I2C_Status_t I2C_Slave_Transmit_IT(I2C_Handle_t *hi2c, uint8_t *pData, uint16_t Size)
{
    // 1. Check parameters
    if(hi2c == NULL || pData == NULL || Size == 0)
        return I2C_ERROR_BERR;

    // 2. Check if handle is free
    if(hi2c->Lock == I2C_LOCKED)
        return I2C_ERROR_BUSY;

    // 3. Lock handle and set state to BUSY_TX
    hi2c->Lock = I2C_LOCKED;
    hi2c->State = I2C_STATE_BUSY_TX;

    // 4. Save buffer and length in handle for IRQ
    hi2c->pTxBuffer = pData;
    hi2c->TxLen = Size;

    // 5. Enable I2C event and error interrupts
    hi2c->Instance->CR2 |= (I2C_CR2_ITEVTEN | I2C_CR2_ITERREN | I2C_CR2_ITBUFEN);

    return I2C_OK;
}

/**
 * @brief  Receive data as I2C slave (interrupt mode)
 * @param  hi2c: pointer to I2C handle
 * @param  pData: pointer to buffer to store received data
 * @param  Size: number of bytes to receive
 * @retval I2C_Status_t: status of reception
 */
I2C_Status_t I2C_Slave_Receive_IT(I2C_Handle_t *hi2c, uint8_t *pData, uint16_t Size)
{
    // 1. Check parameters
    if(hi2c == NULL || pData == NULL || Size == 0)
        return I2C_ERROR_BERR;

    // 2. Check if handle is free
    if(hi2c->Lock == I2C_LOCKED)
        return I2C_ERROR_BUSY;

    // 3. Lock handle and set state to BUSY_RX
    hi2c->Lock = I2C_LOCKED;
    hi2c->State = I2C_STATE_BUSY_RX;

    // 4. Save buffer and length in handle for IRQ
    hi2c->pRxBuffer = pData;
    hi2c->RxLen = Size;

    // 5. Enable I2C event and error interrupts
    hi2c->Instance->CR2 |= (I2C_CR2_ITEVTEN | I2C_CR2_ITERREN | I2C_CR2_ITBUFEN);

    return I2C_OK;
}

/*=========================================================
                IRQ HANDLERS
=========================================================*/
/**
 * @brief  I2C Event IRQ Handler (handles both Master/Slave TX & RX)
 * @param  hi2c: pointer to I2C handle
 * @retval None
 */
void I2C_EV_IRQHandler(I2C_Handle_t *hi2c)
{
    uint32_t sr1 = hi2c->Instance->SR1;
    uint32_t sr2 = hi2c->Instance->SR2;

    // ---------- Start Bit (SB) ----------
    if(sr1 & I2C_SR1_SB)
    {
        if(hi2c->State == I2C_STATE_BUSY_TX)
            hi2c->Instance->DR = (hi2c->DevAddress & ~0x01U); // Write
        else if(hi2c->State == I2C_STATE_BUSY_RX)
            hi2c->Instance->DR = (hi2c->DevAddress | 0x01U);  // Read
    }

    // ---------- Address Sent / Matched ----------
    if(sr1 & I2C_SR1_ADDR)
    {
        sr2 = hi2c->Instance->SR2;  // Clear ADDR flag
        return; // nothing more for master
    }

    // ---------- Transmit / Receive ----------
    if((hi2c->State == I2C_STATE_BUSY_TX) && (sr1 & I2C_SR1_TXE))
    {
        if(hi2c->TxLen > 0)
        {
            hi2c->Instance->DR = *(hi2c->pTxBuffer++);
            hi2c->TxLen--;
        }
    }
    else if((hi2c->State == I2C_STATE_BUSY_RX) && (sr1 & I2C_SR1_RXNE))
    {
        if(hi2c->RxLen > 0)
        {
            *(hi2c->pRxBuffer++) = hi2c->Instance->DR;
            hi2c->RxLen--;
        }
    }

    // ---------- Byte Transfer Finished (BTF) ----------
    if(sr1 & I2C_SR1_BTF)
    {
        if((hi2c->State == I2C_STATE_BUSY_TX) && (hi2c->TxLen == 0))
        {
            I2C_GenerateSTOP(hi2c->Instance);
            I2C_HandleEvent(hi2c, I2C_EVENT_TX_CMPL);
        }
        else if((hi2c->State == I2C_STATE_BUSY_RX) && (hi2c->RxLen == 0))
        {
            I2C_GenerateSTOP(hi2c->Instance);
            I2C_HandleEvent(hi2c, I2C_EVENT_RX_CMPL);
        }
    }

    // ---------- STOP Condition (Slave only) ----------
    if(sr1 & I2C_SR1_STOPF)
    {
        hi2c->Instance->CR1 |= I2C_CR1_PE; // Clear STOPF
        I2C_HandleEvent(hi2c, I2C_EVENT_STOPF);
    }
}

/**
 * @brief  I2C Error IRQ Handler
 * @param  hi2c: pointer to I2C handle
 * @retval None
 */

void I2C_ER_IRQHandler(I2C_Handle_t *hi2c)
{
    uint32_t sr1 = hi2c->Instance->SR1;
    uint32_t error = I2C_ERROR_NONE;

    if(sr1 & I2C_SR1_BERR)      error |= I2C_ERROR_BERR;
    if(sr1 & I2C_SR1_ARLO)      error |= I2C_ERROR_ARLO;
    if(sr1 & I2C_SR1_AF)        error |= I2C_ERROR_AF;
    if(sr1 & I2C_SR1_OVR)       error |= I2C_ERROR_OVR;
    if(sr1 & I2C_SR1_TIMEOUT)   error |= I2C_ERROR_TIMEOUT;

    if(error != I2C_ERROR_NONE)
        I2C_HandleError(hi2c, error);
}
/*=========================================================
                UTILITIES
=========================================================*/

/**
 * @brief  Checks if a slave device is ready for communication (polling)
 * @param  hi2c: pointer to I2C handle
 * @param  DevAddress: 7-bit or 10-bit slave address
 * @param  Trials: number of trials to check readiness
 * @param  Timeout: timeout in ms per trial
 * @retval I2C_Status_t: I2C_OK if ready, else error
 */
I2C_Status_t I2C_IsDeviceReady(I2C_Handle_t *hi2c,uint16_t DevAddress,uint32_t Trials,uint32_t Timeout)
{
    if(!hi2c) return I2C_ERROR_BERR;

    uint32_t trial;
    for(trial = 0; trial < Trials; trial++)
    {
        // Generate START condition
        I2C_GenerateSTART(hi2c->Instance);

        // Wait until SB flag is set
        uint32_t timer = Timeout;
        while(!(hi2c->Instance->SR1 & I2C_SR1_SB))
        {
            if(timer-- == 0)
            {
                I2C_GenerateSTOP(hi2c->Instance);
                break; // timeout for this trial
            }
        }

        // Send slave address with write bit (LSB = 0)
        hi2c->Instance->DR = (DevAddress & ~0x01U);

        // Wait for ACK (ADDR flag set)
        timer = Timeout;
        while(!(hi2c->Instance->SR1 & I2C_SR1_ADDR))
        {
            // Check for NACK or timeout
            if(timer-- == 0 || (hi2c->Instance->SR1 & I2C_SR1_AF))
            {
                // Clear error flags
                hi2c->Instance->SR1 &= ~(I2C_SR1_AF | I2C_SR1_ADDR);
                I2C_GenerateSTOP(hi2c->Instance);
                break; // try next trial
            }
        }

        // If ADDR set → device responded
        if(hi2c->Instance->SR1 & I2C_SR1_ADDR)
        {
            // Clear ADDR flag
            volatile uint32_t temp = hi2c->Instance->SR1;
            temp = hi2c->Instance->SR2;
            (void)temp;

            I2C_GenerateSTOP(hi2c->Instance); // end communication
            return I2C_OK;
        }

        // Wait a short delay before next trial
        for(volatile uint32_t d = 0; d < 5000; d++);
    }

    return I2C_ERROR_BUSY; // Device did not respond after all trials
}
