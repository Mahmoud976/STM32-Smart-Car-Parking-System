#include"GPIO.h"


static uint8_t GPIO_u8GetPinIndex(GPIO_Pin_t Pin)
{
    uint8_t index = 0;

    while (((Pin >> index) & 1U) == 0U)
    {
        index++;
    }

    return index;
}

static inline void GPIO_EnableClock(GPIO_TypeDef_t *PORTx)
{
    if (PORTx == PORTA) RCC_GPIOA_CLK_EN();
    else if (PORTx == PORTB) RCC_GPIOB_CLK_EN();
    else if (PORTx == PORTC) RCC_GPIOC_CLK_EN();
    else if (PORTx == PORTD) RCC_GPIOD_CLK_EN();
    else if (PORTx == PORTE) RCC_GPIOE_CLK_EN();
}
/**
 * @brief        Initializes a GPIO pin according to the given configuration.
 *
 * @param[in]    PinConfigPtr   Pointer to GPIO configuration structure.
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Initialization successful.
 *               @retval E_NOT_OK       NULL pointer passed.
 *               @retval INVALID_PORT   Invalid GPIO port.
 *               @retval INVALID_PIN    Invalid GPIO pin.
 *               @retval INVALID_MODE   Invalid GPIO mode.
 *               @retval INVALID_SPEED  Invalid GPIO speed (for output modes).
 *
 * @pre          GPIO peripheral clock must be enabled before calling this function.
 * @post         The selected pin is configured and ready for use.
 *
 * @note         This function configures pin mode, speed, and pull-up/pull-down settings.
 *
 * @warning      Passing NULL pointer will result in E_NOT_OK.
 */
Std_ReturnType GPIO_InitPin(const GPIO_Config_Pin_t * PinConfig)
{
    Std_ReturnType RetVal = E_OK;

    /* =================== Validation =================== */
    if (PinConfig == NULL)
    {
        RetVal = E_NOT_OK;
    }
    else if (!IS_GPIO_PORT(PinConfig->PORTx))
    {
        RetVal = INVALID_PORT;
    }
    else if (!IS_GPIO_PIN(PinConfig->Pin_Number))
    {
        RetVal = INVALID_PIN;
    }
    else
    {
    	/* =================== ENABLE CLK  FOR  PORT =================== */
    	GPIO_EnableClock(PinConfig->PORTx);
        /* =================== Get Pin Index =================== */
        uint8_t pin_index = GPIO_u8GetPinIndex(PinConfig->Pin_Number);

        volatile uint32_t * reg_ptr = NULL;
        uint8_t local_pin = pin_index;

        /* =================== Select CRL or CRH =================== */
        if (pin_index <= GPIO_CRL_MAX_PIN)
        {
            reg_ptr = &(PinConfig->PORTx->CRL);
        }
        else
        {
            reg_ptr = &(PinConfig->PORTx->CRH);
            local_pin = pin_index - GPIO_PINS_PER_REG;
        }

        uint32_t position = local_pin * GPIO_BITS_PER_PIN;

        /* =================== Clear Old Config =================== */
        *reg_ptr &= ~(GPIO_PIN_MASK << position);

        uint32_t mode = 0U;
        uint32_t cnf  = 0U;

        /* =================== Mode Configuration =================== */
        switch (PinConfig->mode)
        {
            case GPIO_MODE_Analog:
                mode = 0U; cnf = 0U;
                break;

            case GPIO_MODE_Input_FLO:
                mode = 0U; cnf = 1U;
                break;

            case GPIO_MODE_Input_PU:
                mode = 0U; cnf = 2U;
                PinConfig->PORTx->BSRR = PinConfig->Pin_Number;   /* Pull-up */
                break;

            case GPIO_MODE_Input_PD:
                mode = 0U; cnf = 2U;
                PinConfig->PORTx->BRR  = PinConfig->Pin_Number;   /* Pull-down */
                break;

            case GPIO_MODE_Output_PP:
                cnf = 0U;
                break;

            case GPIO_MODE_Output_OD:
                cnf = 1U;
                break;

            case GPIO_MODE_Output_AF_PP:
                cnf = 2U;
                break;

            case GPIO_MODE_Output_AF_OD:
                cnf = 3U;
                break;

            default:
                RetVal = INVALID_MODE;
                break;
        }

        /* =================== Speed Configuration =================== */
        if ((RetVal == E_OK) && IS_GPIO_OUTPUT_MODE(PinConfig->mode))
        {
            switch (PinConfig->Speed)
            {
                case GPIO_SPEED_10M: mode = 1U; break;
                case GPIO_SPEED_2M:  mode = 2U; break;
                case GPIO_SPEED_50M: mode = 3U; break;
                default:
                    RetVal = INVALID_SPEED;
                    break;
            }
        }

        /* =================== Apply Configuration =================== */
        if (RetVal == E_OK)
        {
            uint32_t config = ((cnf << 2U) | mode) << position;
            *reg_ptr |= config;
        }
    }

    return RetVal;
}

/**
 * @brief        De-initializes a specific GPIO pin, resetting it to default state.
 *
 * @param[in]    PORTx         Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 * @param[in]    Pin_Number    GPIO pin to reset (GPIO_PIN0 .. GPIO_PIN15).
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Pin successfully de-initialized.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *               @retval INVALID_PIN    Invalid GPIO pin number.
 *
 * @pre          GPIO peripheral clock must be enabled before calling this function.
 * @post         The selected pin is reset: CRL/CRH cleared, output set LOW.
 *
 * @note         This function only affects the selected pin, not other pins in the port.
 * @warning      Using this on a pin currently in use may interrupt ongoing operations.
 */
Std_ReturnType GPIO_DeInitPin(GPIO_TypeDef_t * PORTx, GPIO_Pin_t Pin_Number)
{
	Std_ReturnType RetVal = E_OK;

	/* =================== Validation =================== */
	if (!IS_GPIO_PORT(PORTx))
	{
		RetVal = INVALID_PORT;
	}
	else if (!IS_GPIO_PIN(Pin_Number))
	{
		RetVal = INVALID_PIN;
	}
	else
	{
    /* =================== Get Pin Index =================== */
		uint8_t pin_index = GPIO_u8GetPinIndex(Pin_Number);

		volatile uint32_t * reg_ptr = NULL;
		uint8_t local_pin = pin_index;

		/* =================== Select CRL or CRH =================== */
		if (pin_index <= GPIO_CRL_MAX_PIN)
		{
			reg_ptr = &(PORTx->CRL);
		}
		else
		{
			reg_ptr = &(PORTx->CRH);
			local_pin = pin_index - GPIO_PINS_PER_REG;
		}

		uint32_t position = local_pin * GPIO_BITS_PER_PIN;

		/* =================== Reset Pin Config =================== */
		*reg_ptr &= ~(GPIO_PIN_MASK << position);

		/* =================== Reset ODR =================== */
		PORTx->BRR = Pin_Number;   /* Clear the pin output (safe default) */
	}

	return RetVal;


}

/**
 * @brief        De-initializes an entire GPIO port, resetting all pins to default state.
 *
 * @param[in]    PORTx   Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Port successfully de-initialized.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *
 * @pre          GPIO peripheral clock must be enabled before calling this function.
 * @post         All pins in the port are reset: CRL/CRH cleared, outputs set LOW.
 *
 * @note         This function affects every pin in the selected port.
 * @warning      Using this on an active port may interrupt all ongoing operations.
 */
Std_ReturnType GPIO_DeInitPort(GPIO_TypeDef_t * PORTx)
{
    Std_ReturnType RetVal = E_OK;

    /* =================== Validation =================== */
    if (!IS_GPIO_PORT(PORTx))
    {
        RetVal = INVALID_PORT;
    }
    else
    {
        /* =================== Reset CRL and CRH =================== */
        PORTx->CRL = 0x44444444;  /* Default reset value for CRL */
        PORTx->CRH = 0x44444444;  /* Default reset value for CRH */

        /* =================== Reset ODR =================== */
        PORTx->BRR = 0xFFFF;       /* Clear all output pins (set LOW) */
    }

    return RetVal;
}


/**
 * @brief        Reads the logic level of a specific GPIO pin.
 *
 * @param[in]    PORTx       Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 * @param[in]    Pin_Number  GPIO pin to read (GPIO_PIN0 .. GPIO_PIN15).
 * @param[out]   ptr_value   Pointer to variable where the pin state will be stored
 *                           (GPIO_LOW / GPIO_HIGH).
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Pin successfully read.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *               @retval INVALID_PIN    Invalid GPIO pin number.
 *               @retval E_NOT_OK       NULL pointer passed for ptr_value.
 *
 * @pre          GPIO peripheral must be initialized.
 * @post         The state of the selected pin is returned in ptr_value.
 *
 * @note         Reading a pin configured as output returns the last written value.
 */
Std_ReturnType GPIO_ReadPin(GPIO_TypeDef_t * PORTx, GPIO_Pin_t Pin_Number, uint8_t * ptr_value)
{
    Std_ReturnType RetVal = E_OK;

    /* =================== Validation =================== */
    if (!IS_GPIO_PORT(PORTx))
    {
        RetVal = INVALID_PORT;
    }
    else if (!IS_GPIO_PIN(Pin_Number))
    {
        RetVal = INVALID_PIN;
    }
    else if (ptr_value == NULL)
    {
        RetVal = E_NOT_OK;
    }
    else
    {
        /* =================== Read pin state =================== */
        if ((PORTx->IDR & Pin_Number) != 0)
        {
            *ptr_value = GPIO_HIGH;
        }
        else
        {
            *ptr_value = GPIO_LOW;
        }
    }

    return RetVal;
}

/**
 * @brief        Reads the logic level of an entire GPIO port.
 *
 * @param[in]    PORTx       Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 * @param[out]   ptr_value   Pointer to variable where the 16-bit port state will be stored.
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Port successfully read.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *               @retval E_NOT_OK       NULL pointer passed for ptr_value.
 *
 * @pre          GPIO peripheral must be initialized.
 * @post         The current state of all pins in the port is returned in ptr_value.
 *
 * @note         Only the lower 16 bits of the IDR register are returned.
 */
Std_ReturnType GPIO_ReadPort(GPIO_TypeDef_t * PORTx, uint16_t * ptr_value)
{
    Std_ReturnType RetVal = E_OK;

    /* =================== Validation =================== */
    if (!IS_GPIO_PORT(PORTx))
    {
        RetVal = INVALID_PORT;
    }
    else if (ptr_value == NULL)
    {
        RetVal = E_NOT_OK;
    }
    else
    {
        /* =================== Read entire port =================== */
        *ptr_value = (uint16_t)(PORTx->IDR & 0xFFFF);
    }

    return RetVal;
}


/**
 * @brief        Writes a logic level to a specific GPIO pin.
 *
 * @param[in]    PORTx       Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 * @param[in]    Pin_Number  GPIO pin to write (GPIO_PIN0 .. GPIO_PIN15).
 * @param[in]    Value       Desired logic level (GPIO_LOW / GPIO_HIGH).
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Pin successfully written.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *               @retval INVALID_PIN    Invalid GPIO pin number.
 *               @retval E_NOT_OK       Invalid value (not GPIO_LOW or GPIO_HIGH).
 *
 * @pre          GPIO peripheral must be initialized.
 * @post         The selected pin output is updated according to Value.
 *
 * @note         Writing to an input pin has no effect.
 */
Std_ReturnType GPIO_WritePin(GPIO_TypeDef_t * PORTx, GPIO_Pin_t Pin_Number, uint8_t Value)
{
    Std_ReturnType RetVal = E_OK;

    /* =================== Validation =================== */
    if (!IS_GPIO_PORT(PORTx))
    {
        RetVal = INVALID_PORT;
    }
    else if (!IS_GPIO_PIN(Pin_Number))
    {
        RetVal = INVALID_PIN;
    }
    else
    {
        /* =================== Write pin value =================== */
        if (Value == GPIO_HIGH)
        {
            PORTx->BSRR = Pin_Number;  /* Set pin */
        }
        else if (Value == GPIO_LOW)
        {
            PORTx->BRR = Pin_Number;   /* Reset pin */
        }
        else
        {
            RetVal = E_NOT_OK;         /* Invalid value */
        }
    }

    return RetVal;
}
/**
 * @brief        Writes a 16-bit value to an entire GPIO port.
 *
 * @param[in]    PORTx   Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 * @param[in]    Value   16-bit value to write to the port.
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Port successfully written.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *
 * @pre          GPIO peripheral must be initialized.
 * @post         All pins in the port are updated according to Value.
 *
 * @note         Only the lower 16 bits of Value are used. Writing to input pins has no effect.
 */
Std_ReturnType GPIO_WritePort(GPIO_TypeDef_t * PORTx, uint16_t Value)
{
    Std_ReturnType RetVal = E_OK;

    /* =================== Validation =================== */
    if (!IS_GPIO_PORT(PORTx))
    {
        RetVal = INVALID_PORT;
    }
    else
    {
        /* =================== Write entire port =================== */
        PORTx->ODR = (uint32_t)(Value & 0xFFFF);
    }

    return RetVal;
}

/**
 * @brief        Toggles the logic level of a specific GPIO pin.
 *
 * @param[in]    PORTx       Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 * @param[in]    Pin_Number  GPIO pin to toggle (GPIO_PIN0 .. GPIO_PIN15).
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Pin successfully toggled.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *               @retval INVALID_PIN    Invalid GPIO pin number.
 *
 * @pre          GPIO peripheral must be initialized.
 * @post         The selected pin logic level is inverted.
 *
 * @note         Toggling an input pin has no effect.
 */
Std_ReturnType GPIO_TogglePin(GPIO_TypeDef_t * PORTx, GPIO_Pin_t Pin_Number)
{
    Std_ReturnType RetVal = E_OK;

    /* =================== Validation =================== */
    if (!IS_GPIO_PORT(PORTx))
    {
        RetVal = INVALID_PORT;
    }
    else if (!IS_GPIO_PIN(Pin_Number))
    {
        RetVal = INVALID_PIN;
    }
    else
    {
        /* =================== Toggle pin =================== */
        PORTx->ODR ^= Pin_Number;
    }

    return RetVal;
}

/**
 * @brief        Toggles the logic level of all pins in a GPIO port.
 *
 * @param[in]    PORTx   Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Port successfully toggled.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *
 * @pre          GPIO peripheral must be initialized.
 * @post         All pins in the port have their logic levels inverted.
 *
 * @note         Only the lower 16 bits are toggled. Toggling input pins has no effect.
 */
Std_ReturnType GPIO_TogglePort(GPIO_TypeDef_t * PORTx)
{
    Std_ReturnType RetVal = E_OK;

    /* =================== Validation =================== */
    if (!IS_GPIO_PORT(PORTx))
    {
        RetVal = INVALID_PORT;
    }
    else
    {
        /* =================== Toggle entire port =================== */
        PORTx->ODR ^= 0xFFFF;  /* Toggle lower 16 bits */
    }

    return RetVal;
}

/**
 * @brief        Locks the configuration of a specific GPIO pin.
 *
 * @param[in]    PORTx       Pointer to GPIO peripheral (PORTA, PORTB, etc.).
 * @param[in]    Pin_Number  GPIO pin to lock (GPIO_PIN0 .. GPIO_PIN15).
 *
 * @return       Std_ReturnType
 *               @retval E_OK           Pin successfully locked.
 *               @retval INVALID_PORT   Invalid GPIO port pointer.
 *               @retval INVALID_PIN    Invalid GPIO pin number.
 *
 * @pre          GPIO peripheral must be initialized.
 * @post         The selected pin configuration is locked and cannot be modified until reset.
 *
 * @note         Lock sequence must be followed as per the reference manual.
 */
Std_ReturnType GPIO_LockPin(GPIO_TypeDef_t * PORTx, GPIO_Pin_t Pin_Number)
{
    Std_ReturnType RetVal = E_OK;
    uint32_t temp;

    /* =================== Validation =================== */
    if (!IS_GPIO_PORT(PORTx))
    {
        RetVal = INVALID_PORT;
    }
    else if (!IS_GPIO_PIN(Pin_Number))
    {
        RetVal = INVALID_PIN;
    }
    else
    {
        /* =================== Lock pin =================== */
        temp = 0x00010000U | Pin_Number;  /* LCKK bit + Pin */
        PORTx->LCKR = Pin_Number;         /* Write Pin number */
        PORTx->LCKR = temp;               /* Set LCKK bit */
        PORTx->LCKR;                       /* Read back (required by reference manual) */
        PORTx->LCKR;                       /* Read back again */
    }

    return RetVal;
}

