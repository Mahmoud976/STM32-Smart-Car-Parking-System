#ifndef I2C_H
#define I2C_H

#include "GPIO.h"
#include "STM32F103C6.h"
#include "RCC.h"


/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
/**************************************  Bit definition  ***************************************/
/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/


/*******************  Bit definition for I2C_CR1 register  ********************/
#define I2C_CR1_PE_Pos                      (0U)
#define I2C_CR1_PE_Msk                      (0x1UL << I2C_CR1_PE_Pos)           /*!< 0x00000001 */
#define I2C_CR1_PE                          I2C_CR1_PE_Msk                     /*!< Peripheral Enable */
#define I2C_CR1_SMBUS_Pos                   (1U)
#define I2C_CR1_SMBUS_Msk                   (0x1UL << I2C_CR1_SMBUS_Pos)        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                       I2C_CR1_SMBUS_Msk                  /*!< SMBus Mode */
#define I2C_CR1_SMBTYPE_Pos                 (3U)
#define I2C_CR1_SMBTYPE_Msk                 (0x1UL << I2C_CR1_SMBTYPE_Pos)      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                     I2C_CR1_SMBTYPE_Msk                /*!< SMBus Type */
#define I2C_CR1_ENARP_Pos                   (4U)
#define I2C_CR1_ENARP_Msk                   (0x1UL << I2C_CR1_ENARP_Pos)        /*!< 0x00000010 */
#define I2C_CR1_ENARP                       I2C_CR1_ENARP_Msk                  /*!< ARP Enable */
#define I2C_CR1_ENPEC_Pos                   (5U)
#define I2C_CR1_ENPEC_Msk                   (0x1UL << I2C_CR1_ENPEC_Pos)        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                       I2C_CR1_ENPEC_Msk                  /*!< PEC Enable */
#define I2C_CR1_ENGC_Pos                    (6U)
#define I2C_CR1_ENGC_Msk                    (0x1UL << I2C_CR1_ENGC_Pos)         /*!< 0x00000040 */
#define I2C_CR1_ENGC                        I2C_CR1_ENGC_Msk                   /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH_Pos               (7U)
#define I2C_CR1_NOSTRETCH_Msk               (0x1UL << I2C_CR1_NOSTRETCH_Pos)    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                   I2C_CR1_NOSTRETCH_Msk              /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_START_Pos                   (8U)
#define I2C_CR1_START_Msk                   (0x1UL << I2C_CR1_START_Pos)        /*!< 0x00000100 */
#define I2C_CR1_START                       I2C_CR1_START_Msk                  /*!< Start Generation */
#define I2C_CR1_STOP_Pos                    (9U)
#define I2C_CR1_STOP_Msk                    (0x1UL << I2C_CR1_STOP_Pos)         /*!< 0x00000200 */
#define I2C_CR1_STOP                        I2C_CR1_STOP_Msk                   /*!< Stop Generation */
#define I2C_CR1_ACK_Pos                     (10U)
#define I2C_CR1_ACK_Msk                     (0x1UL << I2C_CR1_ACK_Pos)          /*!< 0x00000400 */
#define I2C_CR1_ACK                         I2C_CR1_ACK_Msk                    /*!< Acknowledge Enable */
#define I2C_CR1_POS_Pos                     (11U)
#define I2C_CR1_POS_Msk                     (0x1UL << I2C_CR1_POS_Pos)          /*!< 0x00000800 */
#define I2C_CR1_POS                         I2C_CR1_POS_Msk                    /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_PEC_Pos                     (12U)
#define I2C_CR1_PEC_Msk                     (0x1UL << I2C_CR1_PEC_Pos)          /*!< 0x00001000 */
#define I2C_CR1_PEC                         I2C_CR1_PEC_Msk                    /*!< Packet Error Checking */
#define I2C_CR1_ALERT_Pos                   (13U)
#define I2C_CR1_ALERT_Msk                   (0x1UL << I2C_CR1_ALERT_Pos)        /*!< 0x00002000 */
#define I2C_CR1_ALERT                       I2C_CR1_ALERT_Msk                  /*!< SMBus Alert */
#define I2C_CR1_SWRST_Pos                   (15U)
#define I2C_CR1_SWRST_Msk                   (0x1UL << I2C_CR1_SWRST_Pos)        /*!< 0x00008000 */
#define I2C_CR1_SWRST                       I2C_CR1_SWRST_Msk                  /*!< Software Reset */
/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_FREQ_Pos                    (0U)
#define I2C_CR2_FREQ_Msk                    (0x3FUL << I2C_CR2_FREQ_Pos)        /*!< 0x0000003F */
#define I2C_CR2_FREQ                        I2C_CR2_FREQ_Msk                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CR2_ITERREN_Pos                 (8U)
#define I2C_CR2_ITERREN_Msk                 (0x1UL << I2C_CR2_ITERREN_Pos)      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                     I2C_CR2_ITERREN_Msk                /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN_Pos                 (9U)
#define I2C_CR2_ITEVTEN_Msk                 (0x1UL << I2C_CR2_ITEVTEN_Pos)      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                     I2C_CR2_ITEVTEN_Msk                /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN_Pos                 (10U)
#define I2C_CR2_ITBUFEN_Msk                 (0x1UL << I2C_CR2_ITBUFEN_Pos)      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                     I2C_CR2_ITBUFEN_Msk                /*!< Buffer Interrupt Enable */
#define I2C_CR2_DMAEN_Pos                   (11U)
#define I2C_CR2_DMAEN_Msk                   (0x1UL << I2C_CR2_DMAEN_Pos)        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                       I2C_CR2_DMAEN_Msk                  /*!< DMA Requests Enable */
#define I2C_CR2_LAST_Pos                    (12U)
#define I2C_CR2_LAST_Msk                    (0x1UL << I2C_CR2_LAST_Pos)         /*!< 0x00001000 */
#define I2C_CR2_LAST                        I2C_CR2_LAST_Msk                   /*!< DMA Last Transfer */
/*******************  Bit definition for I2C_OAR2 register  *******************/
#define I2C_OAR2_ENDUAL_Pos                 (0U)
#define I2C_OAR2_ENDUAL_Msk                 (0x1UL << I2C_OAR2_ENDUAL_Pos)      /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL                     I2C_OAR2_ENDUAL_Msk                /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos                   (1U)
#define I2C_OAR2_ADD2_Msk          			(0x7FUL << I2C_OAR2_ADD2_Pos)
#define I2C_OAR2_ADD2              			I2C_OAR2_ADD2_Msk
/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_SR1_SB_Pos                      (0U)
#define I2C_SR1_SB_Msk                      (0x1UL << I2C_SR1_SB_Pos)           /*!< 0x00000001 */
#define I2C_SR1_SB                          I2C_SR1_SB_Msk                     /*!< Start Bit (Master mode) */
#define I2C_SR1_ADDR_Pos                    (1U)
#define I2C_SR1_ADDR_Msk                    (0x1UL << I2C_SR1_ADDR_Pos)         /*!< 0x00000002 */
#define I2C_SR1_ADDR                        I2C_SR1_ADDR_Msk                   /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos                     (2U)
#define I2C_SR1_BTF_Msk                     (0x1UL << I2C_SR1_BTF_Pos)          /*!< 0x00000004 */
#define I2C_SR1_BTF                         I2C_SR1_BTF_Msk                    /*!< Byte Transfer Finished */
#define I2C_SR1_ADD10_Pos                   (3U)
#define I2C_SR1_ADD10_Msk                   (0x1UL << I2C_SR1_ADD10_Pos)        /*!< 0x00000008 */
#define I2C_SR1_ADD10                       I2C_SR1_ADD10_Msk                  /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_STOPF_Pos                   (4U)
#define I2C_SR1_STOPF_Msk                   (0x1UL << I2C_SR1_STOPF_Pos)        /*!< 0x00000010 */
#define I2C_SR1_STOPF                       I2C_SR1_STOPF_Msk                  /*!< Stop detection (Slave mode) */
#define I2C_SR1_RXNE_Pos                    (6U)
#define I2C_SR1_RXNE_Msk                    (0x1UL << I2C_SR1_RXNE_Pos)         /*!< 0x00000040 */
#define I2C_SR1_RXNE                        I2C_SR1_RXNE_Msk                   /*!< Data Register not Empty (receivers) */
#define I2C_SR1_TXE_Pos                     (7U)
#define I2C_SR1_TXE_Msk                     (0x1UL << I2C_SR1_TXE_Pos)          /*!< 0x00000080 */
#define I2C_SR1_TXE                         I2C_SR1_TXE_Msk                    /*!< Data Register Empty (transmitters) */
#define I2C_SR1_BERR_Pos                    (8U)
#define I2C_SR1_BERR_Msk                    (0x1UL << I2C_SR1_BERR_Pos)         /*!< 0x00000100 */
#define I2C_SR1_BERR                        I2C_SR1_BERR_Msk                   /*!< Bus Error */
#define I2C_SR1_ARLO_Pos                    (9U)
#define I2C_SR1_ARLO_Msk                    (0x1UL << I2C_SR1_ARLO_Pos)         /*!< 0x00000200 */
#define I2C_SR1_ARLO                        I2C_SR1_ARLO_Msk                   /*!< Arbitration Lost (master mode) */
#define I2C_SR1_AF_Pos                      (10U)
#define I2C_SR1_AF_Msk                      (0x1UL << I2C_SR1_AF_Pos)           /*!< 0x00000400 */
#define I2C_SR1_AF                          I2C_SR1_AF_Msk                     /*!< Acknowledge Failure */
#define I2C_SR1_OVR_Pos                     (11U)
#define I2C_SR1_OVR_Msk                     (0x1UL << I2C_SR1_OVR_Pos)          /*!< 0x00000800 */
#define I2C_SR1_OVR                         I2C_SR1_OVR_Msk                    /*!< Overrun/Underrun */
#define I2C_SR1_PECERR_Pos                  (12U)
#define I2C_SR1_PECERR_Msk                  (0x1UL << I2C_SR1_PECERR_Pos)       /*!< 0x00001000 */
#define I2C_SR1_PECERR                      I2C_SR1_PECERR_Msk                 /*!< PEC Error in reception */
#define I2C_SR1_TIMEOUT_Pos                 (14U)
#define I2C_SR1_TIMEOUT_Msk                 (0x1UL << I2C_SR1_TIMEOUT_Pos)      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                     I2C_SR1_TIMEOUT_Msk                /*!< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT_Pos                (15U)
#define I2C_SR1_SMBALERT_Msk                (0x1UL << I2C_SR1_SMBALERT_Pos)     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                    I2C_SR1_SMBALERT_Msk               /*!< SMBus Alert */

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_SR2_MSL_Pos                     (0U)
#define I2C_SR2_MSL_Msk                     (0x1UL << I2C_SR2_MSL_Pos)          /*!< 0x00000001 */
#define I2C_SR2_MSL                         I2C_SR2_MSL_Msk                    /*!< Master/Slave */
#define I2C_SR2_BUSY_Pos                    (1U)
#define I2C_SR2_BUSY_Msk                    (0x1UL << I2C_SR2_BUSY_Pos)         /*!< 0x00000002 */
#define I2C_SR2_BUSY                        I2C_SR2_BUSY_Msk                   /*!< Bus Busy */
#define I2C_SR2_TRA_Pos                     (2U)
#define I2C_SR2_TRA_Msk                     (0x1UL << I2C_SR2_TRA_Pos)          /*!< 0x00000004 */
#define I2C_SR2_TRA                         I2C_SR2_TRA_Msk                    /*!< Transmitter/Receiver */
#define I2C_SR2_GENCALL_Pos                 (4U)
#define I2C_SR2_GENCALL_Msk                 (0x1UL << I2C_SR2_GENCALL_Pos)      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                     I2C_SR2_GENCALL_Msk                /*!< General Call Address (Slave mode) */
#define I2C_SR2_SMBDEFAULT_Pos              (5U)
#define I2C_SR2_SMBDEFAULT_Msk              (0x1UL << I2C_SR2_SMBDEFAULT_Pos)   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                  I2C_SR2_SMBDEFAULT_Msk             /*!< SMBus Device Default Address (Slave mode) */
#define I2C_SR2_SMBHOST_Pos                 (6U)
#define I2C_SR2_SMBHOST_Msk                 (0x1UL << I2C_SR2_SMBHOST_Pos)      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                     I2C_SR2_SMBHOST_Msk                /*!< SMBus Host Header (Slave mode) */
#define I2C_SR2_DUALF_Pos                   (7U)
#define I2C_SR2_DUALF_Msk                   (0x1UL << I2C_SR2_DUALF_Pos)        /*!< 0x00000080 */
#define I2C_SR2_DUALF                       I2C_SR2_DUALF_Msk                  /*!< Dual Flag (Slave mode) */
#define I2C_SR2_PEC_Pos                     (8U)
#define I2C_SR2_PEC_Msk                     (0xFFUL << I2C_SR2_PEC_Pos)         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                         I2C_SR2_PEC_Msk                    /*!< Packet Error Checking Register */

/*------------------- Bit definitions for I2C_CCR -------------------*/

#define I2C_CCR_FS_Pos      15U
#define I2C_CCR_FS_Msk      (1U << I2C_CCR_FS_Pos)
#define I2C_CCR_FS          I2C_CCR_FS_Msk

#define I2C_CCR_DUTY_Pos    14U
#define I2C_CCR_DUTY_Msk    (1U << I2C_CCR_DUTY_Pos)
#define I2C_CCR_DUTY        I2C_CCR_DUTY_Msk



/**
 * @brief I2C peripheral register map
 * Note: Register order must match the reference manual exactly
 */

/*=========================================================
                I2C REGISTER MAP
=========================================================*/
typedef struct {
	volatile uint32_t CR1;    // Control Register 1
	volatile uint32_t CR2;    // Control Register 2
	volatile uint32_t OAR1;   // Own Address Register 1
	volatile uint32_t OAR2;   // Own Address Register 2
	volatile uint32_t DR;     // Data Register
	volatile uint32_t SR1;    // Status Register 1
	volatile uint32_t SR2;    // Status Register 2
	volatile uint32_t CCR;    // Clock Control Register
	volatile uint32_t TRISE;  // Rise Time Register
} I2C_TypeDef_t;

/*=========================================================
                LOCK
=========================================================*/
typedef enum {
	I2C_UNLOCKED = 0,
	I2C_LOCKED
} I2C_Lock_t;

/*=========================================================
                STATE ENUM
=========================================================*/
typedef enum {
	I2C_STATE_RESET = 0,
	I2C_STATE_READY,
	I2C_STATE_BUSY_TX,
	I2C_STATE_BUSY_RX,
	I2C_STATE_SLAVE_TX,
	I2C_STATE_SLAVE_RX,
	I2C_STATE_ERROR
} I2C_State_t;


/*=========================================================
                ERROR ENUM
=========================================================*/
typedef enum {
	I2C_OK = 0,
	I2C_ERROR_BERR,
	I2C_ERROR_ARLO,
	I2C_ERROR_AF,
	I2C_ERROR_OVR,
	I2C_ERROR_TIMEOUT,
	I2C_ERROR_BUSY,
	I2C_ERROR_INVALID_PARAM
} I2C_Status_t;

/*=========================================================
                Mode ENUM
=========================================================*/
typedef enum {
	I2C_MODE_MASTER,
	I2C_MODE_SLAVE
} I2C_Mode_t;
/*=========================================================
                STOP ENUM
=========================================================*/
typedef enum {
	I2C_STOP,
	I2C_NO_STOP,
	I2C_REPEATED_START
} I2C_StopMode_t;



/*=========================================================
                CALLBACK TYPE
=========================================================*/
typedef void (*I2C_Callback_t)(uint32_t eventFlags);  // For normal events
typedef void (*I2C_ErrorCallback_t)(uint32_t errorFlags);  // For errors

/*=========================================================
                CONFIG STRUCT
=========================================================*/

/**
 * @brief I2C configuration structure
 */
typedef struct {

	uint32_t ClockSpeed;      /*!< Specifies the I2C clock frequency.
                                   This parameter must be a value of @ref I2C_Clock_Speed */

	uint16_t OwnAddress;      /*!< Specifies the device own address.
                                   This parameter must be a value of @ref I2C_Own_Address */

	uint8_t ACKControl;       /*!< Enables or disables ACK.
                                   This parameter must be a value of @ref I2C_ACK_Control */

	uint8_t AddressingMode;   /*!< Specifies addressing mode (7-bit or 10-bit).
                                   This parameter must be a value of @ref I2C_Addressing_Mode */

	uint8_t DualAddress;      /*!< Enables or disables dual addressing mode.
                                   This parameter must be a value of @ref I2C_Dual_Address */

	uint16_t SecondAddress;   /*!< Specifies second address.
                                   This parameter must be a value of @ref I2C_Second_Address */

	uint32_t  IT_Config;      /*!< Enables I2C interrupts.
                                   This parameter must be a combination of @ref I2C_IRQ_Definitions */

    I2C_Callback_t Callback;               // User callback (TX/RX complete or STOP)

    I2C_ErrorCallback_t ErrorCallback;   // User callback for error (OVR, ARLO, BERR)

} I2C_Config_t;

/*=========================================================
                HANDLE STRUCT
=========================================================*/

/**
 * @brief I2C handle structure
 */
typedef struct {

	I2C_TypeDef_t *Instance;  /*!< I2C registers base address.
                                   This parameter must be a value of @ref I2C_Instances */

	I2C_Config_t   Config;    /*!< I2C communication parameters.
                                   This parameter must be configured using @ref I2C_Config_t */

	uint16_t DevAddress;

	I2C_StopMode_t XferOptions;          /*!Transfer options: default, no stop, repeated start */



	volatile const uint8_t *pTxBuffer;      /*!< Pointer to I2C Tx transfer buffer.
                                   This parameter must be a value of @ref I2C_Buffer_Pointer */

	volatile uint8_t  *pRxBuffer;      /*!< Pointer to I2C Rx transfer buffer.
                                   This parameter must be a value of @ref I2C_Buffer_Pointer */

	uint16_t TxLen;           /*!< I2C Tx transfer size.
                                   This parameter must be a value of @ref I2C_Data_Length */

	uint16_t RxLen;           /*!< I2C Rx transfer size.
                                   This parameter must be a value of @ref I2C_Data_Length */

	I2C_State_t  State;           /*!< I2C communication state.
                                   This parameter must be a value of @ref I2C_State_t */

	I2C_Lock_t            Lock;       /*!< Lock for process */
    uint32_t            ErrorCode;  /*!< Stores I2C error codes */

} I2C_Handle_t;


/*=========================================================
                I2C CONFIGURATION REFERENCES
=========================================================*/
#define ENABLE    1
#define DISABLE   0

/**
 * @defgroup I2C_Clock_Speed
 * @{
 */
#define I2C_SM_100K        100000U
#define I2C_FM_400K        400000U
/** @} */


/**
 * @defgroup I2C_Own_Address
 * @{
 */
#define I2C_OWN_ADDRESS_7BIT(ADDR)     (((ADDR & 0x7F) << 1) | (1U << 14))

#define I2C_ADDR_7BIT(addr)            ((addr) << 1)

#define I2C_OWN_ADDRESS_10BIT(ADDR)    (((ADDR & 0x3FF) << 0) | (1U << 15))
/** @} */


/**
 * @defgroup I2C_Addressing_Mode
 * @{
 */
#define I2C_ADDRESS_7BIT_MODE      (0U << 15)
#define I2C_ADDRESS_10BIT_MODE     (1U << 15)
/** @} */


/**
 * @defgroup I2C_ACK_Control
 * @{
 */
#define I2C_ACK_ENABLE     (1U << 10)
#define I2C_ACK_DISABLE    (0U)
/** @} */


/**
 * @defgroup I2C_Dual_Address
 * @{
 */
#define I2C_DUAL_ENABLE    (1U << 0)
#define I2C_DUAL_DISABLE   (0U)
/** @} */


/**
 * @defgroup I2C_Second_Address
 * @{
 */
#define I2C_SECOND_ADDRESS_ENABLE(ADDR)   ((1U << 0) | ((ADDR & 0x7F) << 1))
#define I2C_SECOND_ADDRESS_DISABLE        (0U)
/** @} */



/**
 * @defgroup I2C_Buffer_Pointer
 * @{
 */
#define I2C_BUFFER_NULL    ((void*)0)
/** @} */


/**
 * @defgroup I2C_Data_Length
 * @{
 */
#define I2C_DATA_LENGTH_1      1U
#define I2C_DATA_LENGTH_2      2U
#define I2C_DATA_LENGTH_3      3U
#define I2C_DATA_LENGTH_4      4U
/** @} */


/**
 * @defgroup I2C_IRQ_Definitions
 * @{
 */
#define I2C_IT_EVT   (1U << 0)   /*!< Event Interrupt: Start, Stop, Address matched */
#define I2C_IT_BUF   (1U << 1)   /*!< Buffer Interrupt: TXE, RXNE */
#define I2C_IT_ERR   (1U << 2)   /*!< Error Interrupt: BERR, ARLO, OVR, AF */
/** @} */

/**
 * @defgroup I2C_Callback_Definition
 * @{
 */
#define I2C_CALLBACK_NULL   ((void*)0)
/** @} */


/**
 * @defgroup I2C_Instances
 * @{
 */
#define I2C1   ( (I2C_TypeDef_t *) I2C1_BASE )
#define I2C2   ( (I2C_TypeDef_t *) I2C2_BASE )
/** @} */




// ==========================
// Event flags (for normal operation)
// ==========================
#define I2C_EVENT_NONE      0x00
#define I2C_EVENT_TX_CMPL   0x01   // Transmission complete
#define I2C_EVENT_RX_CMPL   0x02   // Reception complete
#define I2C_EVENT_STOPF     0x04   // STOP condition detected

// ==========================
// Error flags
// ==========================
#define I2C_ERROR_NONE      0x00
#define I2C_ERROR_BERR      0x01   // Bus error
#define I2C_ERROR_ARLO      0x02   // Arbitration lost
#define I2C_ERROR_AF        0x04   // Acknowledge failure
#define I2C_ERROR_OVR       0x08   // Overrun/Underrun
#define I2C_ERROR_TIMEOUT   0x10   // Timeout
/*=========================================================
                INLINE HELPERS
=========================================================*/
static inline void I2C_Enable(I2C_TypeDef_t *I2Cx)
{
	I2Cx->CR1 |= I2C_CR1_PE;
}



static inline void I2C_Disable(I2C_TypeDef_t *I2Cx)
{
	I2Cx->CR1 &= ~(I2C_CR1_PE);
}


static inline void I2C_EnableACK(I2C_TypeDef_t *I2Cx)
{
    I2Cx->CR1 |= I2C_CR1_ACK;
}


static inline void I2C_DisableACK(I2C_TypeDef_t *I2Cx)
{

	I2Cx->CR1 &= ~I2C_CR1_ACK;
}


static inline uint8_t I2C_IsBusy(I2C_TypeDef_t *I2Cx)
{
	return ((I2Cx->SR2 & I2C_SR2_BUSY) ? 1U : 0U);
}


static inline uint8_t I2C_WaitUntilNotBusy(I2C_TypeDef_t *I2Cx, volatile uint32_t timeout)
{
    while (I2C_IsBusy(I2Cx))
    {
        if (timeout-- == 0)
            return 0; // timeout
    }
    return 1;
}


static inline void I2C_GenerateSTART(I2C_TypeDef_t *I2Cx)
{
	I2Cx->CR1 |= I2C_CR1_START;
}



static inline void I2C_GenerateSTOP(I2C_TypeDef_t *I2Cx)
{
	I2Cx->CR1 |= I2C_CR1_STOP;
}



static inline void I2C_ClearADDR(I2C_TypeDef_t *I2Cx)
{
    volatile uint32_t temp;
    temp = I2Cx->SR1;
    temp = I2Cx->SR2;
    (void)temp;
}


static inline uint8_t I2C_GetFlag(I2C_TypeDef_t *I2Cx, uint32_t flag)
{
    return (I2Cx->SR1 & flag) ? 1U : 0U;
}



static inline uint8_t I2C_GetFlag2(I2C_TypeDef_t *I2Cx, uint32_t flag)
{
    return (I2Cx->SR2 & flag) ? 1U : 0U;
}


static inline uint8_t I2C_WaitForFlag(I2C_TypeDef_t *I2Cx, uint32_t flag, volatile uint32_t timeout)
{
    while (!(I2Cx->SR1 & flag))
    {
        if (timeout-- == 0)
            return 0;
    }
    return 1;
}


static inline void I2C_ClearAF(I2C_TypeDef_t *I2Cx)
{
    I2Cx->SR1 &= ~(I2C_SR1_AF);
}


static inline uint8_t I2C_WriteData(I2C_TypeDef_t *I2Cx, uint8_t data, volatile uint32_t timeout)
{
	while (!(I2Cx->SR1 & I2C_SR1_TXE))
	{
		if (I2Cx->SR1 & (I2C_SR1_AF | I2C_SR1_ARLO | I2C_SR1_BERR))
		    return 0;
        if (timeout-- == 0)
            return 0;
    }

    I2Cx->DR = data;
    return 1;
}


static inline uint8_t I2C_ReadData(I2C_TypeDef_t *I2Cx, uint8_t *data, volatile uint32_t timeout)
{
    while (!(I2Cx->SR1 & I2C_SR1_RXNE))
    {
        if (timeout-- == 0)
            return 0;
    }

    *data = (uint8_t)(I2Cx->DR);
    return 1;
}


static inline void I2C_SendAddress(I2C_TypeDef_t *I2Cx, uint16_t addr, uint8_t read)
{
    if (read)
        I2Cx->DR = I2C_ADDR_7BIT(addr) | 1;
    else
        I2Cx->DR = I2C_ADDR_7BIT(addr) & ~1;
}

static inline uint8_t I2C_WaitForFlagClear(I2C_TypeDef_t *I2Cx, uint32_t flag, volatile uint32_t timeout)
{
    while (I2Cx->SR1 & flag)
    {
        if (timeout-- == 0)
            return 0;
    }
    return 1;
}





/**
 * @brief Clear the I2C STOP flag
 * @param hi2c: pointer to I2C handle
 */
static void I2C_ClearSTOPFlag(I2C_Handle_t *hi2c)
{
    // Reading SR1 ثم كتابة CR1 يمسح STOPF
    volatile uint32_t temp = hi2c->Instance->SR1;
    (void)temp;
    hi2c->Instance->CR1 |= I2C_CR1_PE;  // Re-enable peripheral to clear STOPF
}


/**
 * @brief  Enable I2C interrupts (NVIC + peripheral) for given I2C instance
 * @param  I2Cx: pointer to I2C peripheral (I2C1, I2C2, etc.)
 */
static void I2C_EnableIRQ(I2C_TypeDef_t *I2Cx)
{
    // 1. Enable NVIC
    if (I2Cx == I2C1)
    {
        NVIC_I2C1_EV_Enable;
        NVIC_I2C1_ER_Enable;
    }
    else if (I2Cx == I2C2)
    {
        NVIC_I2C2_EV_Enable;
        NVIC_I2C2_ER_Enable;
    }

    // 2. Enable I2C peripheral interrupts (Event, Buffer, Error)
    I2Cx->CR2 |= (I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN | I2C_CR2_ITERREN);
}

/**
 * @brief  Disable I2C interrupts (NVIC + peripheral) for given I2C instance
 * @param  I2Cx: pointer to I2C peripheral (I2C1, I2C2, etc.)
 */
static void I2C_DisableIRQ(I2C_TypeDef_t *I2Cx)
{
    // 1. Disable NVIC
    if (I2Cx == I2C1)
    {
        NVIC_I2C1_EV_Disable;
        NVIC_I2C1_ER_Disable;
    }
    else if (I2Cx == I2C2)
    {
        NVIC_I2C2_EV_Disable;
        NVIC_I2C2_ER_Disable;
    }

    // 2. Disable I2C peripheral interrupts
    I2Cx->CR2 &= ~(I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN | I2C_CR2_ITERREN);
}

/*=========================================================
                API PROTOTYPES
=========================================================*/
/**
 * @brief  Returns the default I2C configuration
 * @retval I2C_Config_t: structure with default settings
 */
I2C_Config_t I2C_DefaultConfig(void);
/*=========================================================
                BUS RECOVERY
=========================================================*/

/**
 * @brief  Tries to recover the I2C bus in case of stuck lines
 * @param  hi2c: pointer to I2C handle
 * @retval None
 */
void I2C_BusRecover(I2C_Handle_t *hi2c);
/*=========================================================
                PERIPHERAL CLOCK
=========================================================*/
/**
 * @brief  Enables or disables peripheral clock for given I2C
 * @param  I2Cx: pointer to I2C peripheral
 * @param  EnOrDi: ENABLE or DISABLE
 * @retval None
 */
void I2C_PeriClockControl(I2C_TypeDef_t *I2Cx, uint8_t EnOrDi);

/**
 * @brief  Initializes the I2C peripheral
 * @param  hi2c: pointer to I2C handle with configuration
 * @retval I2C_Status_t: status of initialization
 */
I2C_Status_t I2C_Init(I2C_Handle_t *hi2c);
/**
 * @brief  Deinitializes the I2C peripheral
 * @param  hi2c: pointer to I2C handle
 * @retval I2C_Status_t: status of deinitialization
 */
I2C_Status_t I2C_DeInit(I2C_Handle_t *hi2c);



/*================ MASTER APIs ================*/

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
I2C_Status_t I2C_Master_Transmit(
		I2C_Handle_t *hi2c,
		uint16_t DevAddress,
		const uint8_t *pData,
		uint16_t Size,
		I2C_StopMode_t StopMode,
		uint32_t Timeout
);
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
I2C_Status_t I2C_Master_Receive(
		I2C_Handle_t *hi2c,
		uint16_t DevAddress,
		uint8_t *pData,
		uint16_t Size,
		I2C_StopMode_t StopMode,
		uint32_t Timeout
);

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
I2C_Status_t I2C_Master_Transmit_IT(
		I2C_Handle_t *hi2c,
		uint16_t DevAddress,
		const uint8_t *pData,
		uint16_t Size
);
/**
 * @brief  Initiates I2C master reception in non-blocking interrupt mode
 * @param  hi2c: pointer to I2C handle
 * @param  DevAddress: 7/10-bit slave address
 * @param  pData: pointer to buffer to store received data
 * @param  Size: number of bytes to receive
 * @retval I2C_Status_t: status of reception initiation
 */
I2C_Status_t I2C_Master_Receive_IT(
		I2C_Handle_t *hi2c,
		uint16_t DevAddress,
		uint8_t *pData,
		uint16_t Size
);

/*================ SLAVE APIs ================*/

/**
 * @brief  Sends data in slave mode
 * @param  hi2c: pointer to I2C handle
 * @param  pData: pointer to data buffer
 * @param  Size: number of bytes to transmit
 * @retval I2C_Status_t: status of transmission
 */
I2C_Status_t I2C_Slave_Transmit(I2C_Handle_t *hi2c,const uint8_t *pData,uint16_t Size);


/**
 * @brief  Receives data in slave mode
 * @param  hi2c: pointer to I2C handle
 * @param  pData: pointer to buffer to store received data
 * @param  Size: number of bytes to receive
 * @retval I2C_Status_t: status of reception
 */
I2C_Status_t I2C_Slave_Receive(I2C_Handle_t *hi2c, uint8_t *pData,uint16_t Size);


/**
 * @brief  Transmit data as I2C slave (interrupt mode)
 * @param  hi2c: pointer to I2C handle
 * @param  pData: pointer to data buffer
 * @param  Size: number of bytes to send
 * @retval I2C_Status_t: status of transmission
 */
I2C_Status_t I2C_Slave_Transmit_IT(I2C_Handle_t *hi2c, uint8_t *pData, uint16_t Size);

/**
 * @brief  Receive data as I2C slave (interrupt mode)
 * @param  hi2c: pointer to I2C handle
 * @param  pData: pointer to buffer to store received data
 * @param  Size: number of bytes to receive
 * @retval I2C_Status_t: status of reception
 */
I2C_Status_t I2C_Slave_Receive_IT(I2C_Handle_t *hi2c, uint8_t *pData, uint16_t Size);

/*================ UTILITIES ================*/
/**
 * @brief  Checks if device is ready for communication
 * @param  hi2c: pointer to I2C handle
 * @param  DevAddress: slave device address
 * @param  Trials: number of trials
 * @param  Timeout: timeout per trial
 * @retval I2C_Status_t: I2C_OK if ready, else error
 */
I2C_Status_t I2C_IsDeviceReady(
		I2C_Handle_t *hi2c,
		uint16_t DevAddress,
		uint32_t Trials,
		uint32_t Timeout
);


#endif /* I2C_H */
