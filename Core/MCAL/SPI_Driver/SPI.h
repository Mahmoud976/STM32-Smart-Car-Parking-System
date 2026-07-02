#ifndef SPI_H
#define SPI_H

#include "GPIO.h"
#include "RCC.h"

//============================//
//        MACROS              //
//============================//


#define SPI_SR_TXE   (1 << 1)
#define SPI_SR_RXNE  (1 << 0)
#define SPI_SR_BSY   (1 << 7)

#define WAIT_FOR_TXE(SPIx) while(!((SPIx)->SR & SPI_SR_TXE))
#define WAIT_FOR_RXNE(SPIx) while(!((SPIx)->SR & SPI_SR_RXNE))
#define WAIT_FOR_BSY(SPIx) while((SPIx)->SR & SPI_SR_BSY)


#define SPI_SR_TXE_BIT  1
#define SPI_SR_RXNE_BIT 0
#define SPI_SR_ERR_BIT  4



/////////////////////////////////////////////////////
//              SPI Registers Definition
/////////////////////////////////////////////////////

/**
 * @brief SPI peripheral register map
 * Note: Register order must match the reference manual exactly
 */
typedef struct {
    volatile uint32_t CR1;     // Control Register 1
    volatile uint32_t CR2;     // Control Register 2
    volatile uint32_t SR;      // Status Register
    volatile uint32_t DR;      // Data Register
    volatile uint32_t CRCPR;   // CRC Polynomial Register
    volatile uint32_t RXCRCR;  // RX CRC Register
    volatile uint32_t TXCRCR;  // TX CRC Register
    volatile uint32_t I2SCFGR; // I2S Configuration Register
    volatile uint32_t I2SPR;   // I2S Prescaler Register
} SPI_TypeDef_t;

/////////////////////////////////////////////////////
//              SPI Instances
/////////////////////////////////////////////////////

#define SPI1     ((SPI_TypeDef_t *)SPI1_BASE)
#define SPI2     ((SPI_TypeDef_t *)SPI2_BASE)


/////////////////////////////////////////////////////
//              IRQ Source Structure
/////////////////////////////////////////////////////

/**
 * @brief SPI interrupt source flags passed to callback
 */
typedef struct {
    uint8_t TXE     :1; // Transmit buffer empty
    uint8_t RXNE    :1; // Receive buffer not empty
    uint8_t ERROR   :1; // Error occurred
    uint8_t Reserved:5;
} SPI_IRQ_Source_t;

/////////////////////////////////////////////////////
//              Callback Type
/////////////////////////////////////////////////////

/**
 * @brief SPI IRQ callback function type
 */
typedef void (*SPI_Callback_t)(SPI_IRQ_Source_t irq_src);

/////////////////////////////////////////////////////
//              SPI Configuration Structure
/////////////////////////////////////////////////////

/**
 * @brief SPI configuration structure
 */
typedef struct {
    SPI_TypeDef_t *Instance;   // SPI instance (SPI1, SPI2, ...)

    uint16_t Mode;             // Master or Slave (@ref SPI_Mode)
    uint16_t Direction;        // Communication mode (@ref SPI_DIRECTION)

    uint16_t FrameFormat;      // MSB/LSB first (@ref SPI_FRAME_FORMAT)
    uint16_t DataSize;         // 8-bit or 16-bit (@ref SPI_DATA_SIZE)
    uint16_t ClockPolarity;    // Clock polarity (@ref SPI_CLK_POLARITY)
    uint16_t ClockPhase;       // Clock phase (@ref SPI_CLK_PHASE)
    uint16_t NSS;              // Slave select management (@ref SPI_NSS)
    uint16_t BaudRate;         // Baud rate prescaler (@ref SPI_BaudRate)

    uint32_t IRQ_Enable;       // Interrupt enable (@ref SPI_IRQ)

    SPI_Callback_t Callback;   // IRQ callback

} SPI_Config_t;

/////////////////////////////////////////////////////
//              Return Status
/////////////////////////////////////////////////////

typedef enum {
    SPI_OK,
    SPI_BUSY,
    SPI_ERROR,
    SPI_INVALID_PTR,
    SPI_INVALID_LENGTH,
} SPI_Status_t;

/////////////////////////////////////////////////////
//              SPI Modes
/////////////////////////////////////////////////////

#define SPI_MODE_SLAVE     (0U)
#define SPI_MODE_MASTER    (1U << 2)

/////////////////////////////////////////////////////
//              Communication Modes
/////////////////////////////////////////////////////

#define SPI_DIRECTION_FULL_DUPLEX        (0U)
#define SPI_DIRECTION_SIMPLEX_RX         (1U << 10)
#define SPI_DIRECTION_HALF_DUPLEX_RX     (1U << 15)
#define SPI_DIRECTION_HALF_DUPLEX_TX     ((1U << 15) | (1U << 14))

/////////////////////////////////////////////////////
//              Data Size
/////////////////////////////////////////////////////

#define SPI_DATASIZE_8BIT   (0U)
#define SPI_DATASIZE_16BIT  (1U << 11)

/////////////////////////////////////////////////////
//              Frame Format
/////////////////////////////////////////////////////

#define SPI_FIRSTBIT_MSB   (0U)
#define SPI_FIRSTBIT_LSB   (1U << 7)

/////////////////////////////////////////////////////
//              Clock Configuration
/////////////////////////////////////////////////////

#define SPI_POLARITY_LOW   (0U)
#define SPI_POLARITY_HIGH  (1U << 1)

#define SPI_PHASE_1EDGE    (0U)
#define SPI_PHASE_2EDGE    (1U << 0)

/////////////////////////////////////////////////////
//              NSS Configuration
/////////////////////////////////////////////////////

#define SPI_NSS_HW_SLAVE              (0U)
#define SPI_NSS_HW_MASTER_ENABLE      (1U << 2)
#define SPI_NSS_HW_MASTER_DISABLE     (0U)

#define SPI_NSS_SW_RESET              (1U << 9)
#define SPI_NSS_SW_SET                ((1U << 9) | (1U << 8))

/////////////////////////////////////////////////////
//              Baud Rate Prescaler
/////////////////////////////////////////////////////

#define SPI_BAUDRATE_DIV2     (0U)
#define SPI_BAUDRATE_DIV4     (0b001U << 3)
#define SPI_BAUDRATE_DIV8     (0b010U << 3)
#define SPI_BAUDRATE_DIV16    (0b011U << 3)
#define SPI_BAUDRATE_DIV32    (0b100U << 3)
#define SPI_BAUDRATE_DIV64    (0b101U << 3)
#define SPI_BAUDRATE_DIV128   (0b110U << 3)
#define SPI_BAUDRATE_DIV256   (0b111U << 3)

/////////////////////////////////////////////////////
//              Interrupt Enable
/////////////////////////////////////////////////////

#define SPI_IRQ_NONE     (0U)
#define SPI_IRQ_TXE      (1U << 7)
#define SPI_IRQ_RXNE     (1U << 6)
#define SPI_IRQ_ERROR    (1U << 5)

/////////////////////////////////////////////////////
//              APIs
/////////////////////////////////////////////////////

/**
 * @brief Initialize the SPI peripheral with the given configuration
 *
 * @param[in] Config Pointer to SPI configuration structure
 *
 * @return SPI_Status_t
 *         - SPI_OK: Initialization successful
 *         - SPI_INVALID_PTR: Null pointer passed
 *         - SPI_ERROR: Configuration or hardware setup failed
 *
 * @note This function:
 *       - Configures SPI control registers (CR1, CR2)
 *       - Sets communication mode, clock, frame format, and baud rate
 *       - Enables SPI peripheral clock
 *       - Does NOT start any data transfer
 */
SPI_Status_t SPI_Init(SPI_Config_t *Config);

/**
 * @brief Deinitialize the SPI peripheral
 *
 * @param[in] Config Pointer to SPI configuration structure
 *
 * @return SPI_Status_t
 *         - SPI_OK: Deinitialization successful
 *         - SPI_INVALID_PTR: Null pointer passed
 *
 * @note This function:
 *       - Resets SPI registers to default values
 *       - Disables the SPI peripheral
 *       - Disables interrupts if enabled
 */
SPI_Status_t SPI_DeInit(SPI_Config_t *Config);

/**
 * @brief Transmit data over SPI (blocking mode)
 *
 * @param[in] Config Pointer to SPI configuration structure
 * @param[in] pData  Pointer to data buffer to transmit
 * @param[in] Length Number of data elements to transmit
 *
 * @return SPI_Status_t
 *         - SPI_OK: Transmission completed successfully
 *         - SPI_BUSY: Peripheral is busy transmitting previous data
 *         - SPI_INVALID_PTR: Null pointer passed
 *         - SPI_INVALID_LENGTH: Length is zero
 *
 * @note This function:
 *       - Waits for TXE (Transmit buffer empty) flag before writing data
 *       - Sends data sequentially in a blocking manner
 *       - Does NOT use interrupts or DMA
 */
SPI_Status_t SPI_Send(SPI_Config_t *Config, const uint16_t *pData, uint32_t Length);

/**
 * @brief Receive data over SPI (blocking mode)
 *
 * @param[in]  Config Pointer to SPI configuration structure
 * @param[out] pData  Pointer to buffer to store received data
 * @param[in]  Length Number of data elements to receive
 *
 * @return SPI_Status_t
 *         - SPI_OK: Reception completed successfully
 *         - SPI_BUSY: Peripheral is busy
 *         - SPI_INVALID_PTR: Null pointer passed
 *         - SPI_INVALID_LENGTH: Length is zero
 *
 * @note This function:
 *       - Waits for RXNE (Receive buffer not empty) flag
 *       - Reads incoming data into provided buffer
 *       - In master mode, dummy data may be sent to generate clock
 */
SPI_Status_t SPI_Receive(SPI_Config_t *Config, uint16_t *pData, uint32_t Length);

/**
 * @brief Perform full-duplex SPI transmit and receive (blocking mode)
 *
 * @param[in]     Config Pointer to SPI configuration structure
 * @param[in,out] pData  Pointer to data buffer (TX data will be overwritten by RX data)
 * @param[in]     Length Number of data elements to transfer
 *
 * @return SPI_Status_t
 *         - SPI_OK: Operation completed successfully
 *         - SPI_BUSY: Peripheral is busy
 *         - SPI_INVALID_PTR: Null pointer passed
 *         - SPI_INVALID_LENGTH: Length is zero
 *
 * @note This function:
 *       - Sends and receives data simultaneously (full-duplex)
 *       - Waits for TXE and RXNE flags during operation
 *       - Overwrites transmitted data with received data in the same buffer
 */
SPI_Status_t SPI_TransmitReceive(SPI_Config_t *Config, uint16_t *pData, uint32_t Length);

#endif // SPI_H
