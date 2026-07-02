#ifndef EEPROM_AT24C512B_H
#define EEPROM_AT24C512B_H

#include "I2C.h"

// AT24C512B memory size
#define AT24C512B_PAGE_SIZE   128   // 128 bytes per page
#define AT24C512B_TOTAL_SIZE  65536 // 512Kbit = 64KB

// Device address (A2,A1,A0 pins = 0)
#define AT24C512B_BASE_ADDR   0x50  // 7-bit address

// Status codes
typedef enum {
    AT24C512B_OK = 0,
    AT24C512B_ERROR,
    AT24C512B_TIMEOUT
} AT24C512B_Status_t;

// Prototypes
AT24C512B_Status_t AT24C512B_WriteByte(I2C_Handle_t *hi2c, uint16_t memAddr, uint8_t data, uint32_t timeout);
AT24C512B_Status_t AT24C512B_ReadByte(I2C_Handle_t *hi2c, uint16_t memAddr, uint8_t *data, uint32_t timeout);

AT24C512B_Status_t AT24C512B_WritePage(I2C_Handle_t *hi2c, uint16_t memAddr, const uint8_t *pData, uint16_t length, uint32_t timeout);
AT24C512B_Status_t AT24C512B_ReadSequential(I2C_Handle_t *hi2c, uint16_t memAddr, uint8_t *pData, uint16_t length, uint32_t timeout);


AT24C512B_Status_t AT24C512B_WriteByte_IT(I2C_Handle_t *hi2c, uint16_t memAddr, uint8_t data, uint32_t timeout);
AT24C512B_Status_t AT24C512B_ReadByte_IT(I2C_Handle_t *hi2c, uint16_t memAddr, uint8_t *data, uint32_t timeout);

AT24C512B_Status_t AT24C512B_WritePage_IT(I2C_Handle_t *hi2c, uint16_t memAddr, const uint8_t *pData, uint16_t length, uint32_t timeout);
AT24C512B_Status_t AT24C512B_ReadSequential_IT(I2C_Handle_t *hi2c, uint16_t memAddr, uint8_t *pData, uint16_t length, uint32_t timeout);




#endif
