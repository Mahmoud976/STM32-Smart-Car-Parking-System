#include "SPI.h"

//============================//
//     GLOBAL CALLBACKS       //
//============================//
void (*Gp_SPI_CALLBACK[2])(SPI_IRQ_Source_t irq_src) = {NULL, NULL};


//============================//
//     STATIC HELPER          //
//============================//
static void SPI_InitPins(SPI_Config_t *Config)
{
    GPIO_Config_Pin_t pin_cfg;

    if(Config->Instance == SPI1)
    {
        // SPI1: PA4-PA7
        RCC_SPI1_CLK_EN();
        NVIC_SPI1_Enable;
        Gp_SPI_CALLBACK[0] = Config->Callback;

        if(Config->Mode == SPI_MODE_MASTER)
        {
            // NSS
            pin_cfg.PORTx = PORTA;
            pin_cfg.Pin_Number = GPIO_PIN4;
            pin_cfg.mode = (Config->NSS == SPI_NSS_HW_MASTER_DISABLE) ?
                            GPIO_MODE_Output_AF_PP : GPIO_MODE_Input_FLO;
            pin_cfg.Speed = GPIO_SPEED_10M;
            GPIO_InitPin(&pin_cfg);

            // SCK
            pin_cfg.Pin_Number = GPIO_PIN5;
            pin_cfg.mode = GPIO_MODE_Output_AF_PP;
            GPIO_InitPin(&pin_cfg);

            // MISO
            pin_cfg.Pin_Number = GPIO_PIN6;
            pin_cfg.mode = GPIO_MODE_Input_FLO;
            GPIO_InitPin(&pin_cfg);

            // MOSI
            pin_cfg.Pin_Number = GPIO_PIN7;
            pin_cfg.mode = GPIO_MODE_Output_AF_PP;
            GPIO_InitPin(&pin_cfg);
        }
        else
        {
            // SLAVE configuration
            pin_cfg.PORTx = PORTA;

            // NSS
            if(Config->NSS == SPI_NSS_HW_SLAVE)
            {
                pin_cfg.Pin_Number = GPIO_PIN4;
                pin_cfg.mode = GPIO_MODE_Input_FLO;
                GPIO_InitPin(&pin_cfg);
            }
            // SCK
            pin_cfg.Pin_Number = GPIO_PIN5;
            pin_cfg.mode = GPIO_MODE_Input_FLO;
            GPIO_InitPin(&pin_cfg);
            // MISO
            pin_cfg.Pin_Number = GPIO_PIN6;
            pin_cfg.mode = GPIO_MODE_Output_AF_PP;
            GPIO_InitPin(&pin_cfg);
            // MOSI
            pin_cfg.Pin_Number = GPIO_PIN7;
            pin_cfg.mode = GPIO_MODE_Input_FLO;
            GPIO_InitPin(&pin_cfg);
        }
    }
    else if(Config->Instance == SPI2)
    {
        // SPI2: PB12-PB15
        RCC_SPI2_CLK_EN();
        NVIC_SPI2_Enable;
        Gp_SPI_CALLBACK[1] = Config->Callback;

        if(Config->Mode == SPI_MODE_MASTER)
        {
            // NSS
            pin_cfg.PORTx = PORTB;
            pin_cfg.Pin_Number = GPIO_PIN12;
            pin_cfg.mode = (Config->NSS == SPI_NSS_HW_MASTER_DISABLE) ?
                            GPIO_MODE_Output_AF_PP : GPIO_MODE_Input_FLO;
            pin_cfg.Speed = GPIO_SPEED_10M;
            GPIO_InitPin(&pin_cfg);

            // SCK
            pin_cfg.Pin_Number = GPIO_PIN13;
            pin_cfg.mode = GPIO_MODE_Output_AF_PP;
            GPIO_InitPin(&pin_cfg);

            // MISO
            pin_cfg.Pin_Number = GPIO_PIN14;
            pin_cfg.mode = GPIO_MODE_Input_FLO;
            GPIO_InitPin(&pin_cfg);

            // MOSI
            pin_cfg.Pin_Number = GPIO_PIN15;
            pin_cfg.mode = GPIO_MODE_Output_AF_PP;
            GPIO_InitPin(&pin_cfg);
        }
        else
        {
            // SLAVE
            pin_cfg.PORTx = PORTB;

            // NSS
            if(Config->NSS == SPI_NSS_HW_SLAVE)
            {
                pin_cfg.Pin_Number = GPIO_PIN12;
                pin_cfg.mode = GPIO_MODE_Input_FLO;
                GPIO_InitPin(&pin_cfg);
            }
            // SCK
            pin_cfg.Pin_Number = GPIO_PIN13;
            pin_cfg.mode = GPIO_MODE_Input_FLO;
            GPIO_InitPin(&pin_cfg);
            // MISO
            pin_cfg.Pin_Number = GPIO_PIN14;
            pin_cfg.mode = GPIO_MODE_Output_AF_PP;
            GPIO_InitPin(&pin_cfg);
            // MOSI
            pin_cfg.Pin_Number = GPIO_PIN15;
            pin_cfg.mode = GPIO_MODE_Input_FLO;
            GPIO_InitPin(&pin_cfg);
        }
    }
}

//============================//
//     SPI API FUNCTIONS      //
//============================//

/**
 * @brief Initialize SPI peripheral with configuration
 */
SPI_Status_t SPI_Init(SPI_Config_t *Config)
{
    if(Config == NULL || Config->Instance == NULL)
        return SPI_INVALID_PTR;

    SPI_InitPins(Config);

    // CR1 configuration
    Config->Instance->CR1 = Config->Mode
                           | Config->Direction
                           | Config->FrameFormat
                           | Config->DataSize
                           | Config->ClockPolarity
                           | Config->ClockPhase
                           | Config->BaudRate;

    // CR2 configuration
    if(Config->NSS == SPI_NSS_HW_MASTER_ENABLE || Config->NSS == SPI_NSS_HW_MASTER_DISABLE)
        Config->Instance->CR2 = Config->NSS;

    Config->Instance->CR2 |= Config->IRQ_Enable;

    // Enable SPI
    Config->Instance->CR1 |= (1 << 6);

    return SPI_OK;
}

/**
 * @brief Deinitialize SPI peripheral
 */
SPI_Status_t SPI_DeInit(SPI_Config_t *Config)
{
    if(Config == NULL || Config->Instance == NULL)
        return SPI_INVALID_PTR;

    if(Config->Instance == SPI1)
    {
        RCC_SPI1_CLK_Reset();
        NVIC_SPI1_Disable;
    }
    else if(Config->Instance == SPI2)
    {
        RCC_SPI2_CLK_Reset();
        NVIC_SPI2_Disable;
    }
    else
        return SPI_ERROR;

    return SPI_OK;
}

/**
 * @brief Blocking transmit
 */
SPI_Status_t SPI_Send(SPI_Config_t *Config, const uint16_t *pData, uint32_t Length)
{
    if(Config == NULL || Config->Instance == NULL || pData == NULL)
        return SPI_INVALID_PTR;
    if(Length == 0)
        return SPI_INVALID_LENGTH;

    if(Config->IRQ_Enable == SPI_IRQ_NONE)
    {
        while(Length--)
        {
            WAIT_FOR_TXE(Config->Instance);

            if(Config->DataSize == SPI_DATASIZE_8BIT)
                *((volatile uint8_t *)&Config->Instance->DR) = *((const uint8_t *)pData++);
            else
                Config->Instance->DR = *pData++;
        }

        WAIT_FOR_BSY(Config->Instance);
    }

    return SPI_OK;
}

/**
 * @brief Blocking receive (master generates clock)
 */
SPI_Status_t SPI_Receive(SPI_Config_t *Config, uint16_t *pData, uint32_t Length)
{
    if(Config == NULL || Config->Instance == NULL || pData == NULL)
        return SPI_INVALID_PTR;
    if(Length == 0)
        return SPI_INVALID_LENGTH;

    if(Config->IRQ_Enable == SPI_IRQ_NONE)
    {
        while(Length--)
        {
            // Master mode generates clock
            if(Config->DataSize == SPI_DATASIZE_8BIT)
                *((volatile uint8_t *)&Config->Instance->DR) = 0xFF;
            else
                Config->Instance->DR = 0xFFFF;

            WAIT_FOR_RXNE(Config->Instance);

            if(Config->DataSize == SPI_DATASIZE_8BIT)
                *((uint8_t *)pData++) = *((volatile uint8_t *)&Config->Instance->DR);
            else
                *pData++ = Config->Instance->DR;
        }

        WAIT_FOR_BSY(Config->Instance);
    }

    return SPI_OK;
}

/**
 * @brief Full-duplex transmit & receive
 */
SPI_Status_t SPI_TransmitReceive(SPI_Config_t *Config, uint16_t *pData, uint32_t Length)
{
    if(Config == NULL || Config->Instance == NULL || pData == NULL)
        return SPI_INVALID_PTR;
    if(Length == 0)
        return SPI_INVALID_LENGTH;

    if(Config->IRQ_Enable == SPI_IRQ_NONE)
    {
        while(Length--)
        {
            WAIT_FOR_TXE(Config->Instance);

            if(Config->DataSize == SPI_DATASIZE_8BIT)
                *((volatile uint8_t *)&Config->Instance->DR) = *((uint8_t *)pData);
            else
                Config->Instance->DR = *pData;

            WAIT_FOR_RXNE(Config->Instance);

            if(Config->DataSize == SPI_DATASIZE_8BIT)
                *((uint8_t *)pData++) = *((volatile uint8_t *)&Config->Instance->DR);
            else
                *pData++ = Config->Instance->DR;
        }

        WAIT_FOR_BSY(Config->Instance);
    }

    return SPI_OK;
}

//============================//
//     SPI IRQ HANDLERS       //
//============================//
void SPI1_IRQHandler(void)
{
    SPI_IRQ_Source_t ir;
    ir.TXE   = (SPI1->SR >> SPI_SR_TXE_BIT) & 1U;
    ir.RXNE  = (SPI1->SR >> SPI_SR_RXNE_BIT) & 1U;
    ir.ERROR = (SPI1->SR >> SPI_SR_ERR_BIT) & 1U;

    if(Gp_SPI_CALLBACK[0] != NULL)
        Gp_SPI_CALLBACK[0](ir);
}

void SPI2_IRQHandler(void)
{
    SPI_IRQ_Source_t ir;
    ir.TXE   = (SPI2->SR >> SPI_SR_TXE_BIT) & 1U;
    ir.RXNE  = (SPI2->SR >> SPI_SR_RXNE_BIT) & 1U;
    ir.ERROR = (SPI2->SR >> SPI_SR_ERR_BIT) & 1U;

    if(Gp_SPI_CALLBACK[1] != NULL)
        Gp_SPI_CALLBACK[1](ir);
}
