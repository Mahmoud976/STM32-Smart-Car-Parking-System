#include "EEPROM_AT24C512B.h"

/* ===========================
   AT24C512B Base Address
   =========================== */
#define AT24C512B_BASE_ADDR 0x50  // 7-bit I2C address

/* ===========================
   Write a single byte
   =========================== */
AT24C512B_Status_t AT24C512B_WriteByte(I2C_Handle_t *hi2c, uint16_t memAddr, uint8_t data, uint32_t timeout)
{
    uint8_t buf[3];
    buf[0] = (uint8_t)(memAddr >> 8);   // high byte of memory address
    buf[1] = (uint8_t)(memAddr & 0xFF); // low byte of memory address
    buf[2] = data;

    // Send memory address + data (Master Transmit Blocking)
    if(I2C_Master_Transmit(hi2c, AT24C512B_BASE_ADDR, buf, 3, I2C_STOP, timeout) != I2C_OK)
        return AT24C512B_ERROR;

    // Wait until EEPROM completes internal write cycle
    if(I2C_IsDeviceReady(hi2c, AT24C512B_BASE_ADDR, 100, timeout) != I2C_OK)
        return AT24C512B_TIMEOUT;

    return AT24C512B_OK;
}

/* ===========================
   Write a page (up to 128 bytes)
   =========================== */
AT24C512B_Status_t AT24C512B_WritePage(I2C_Handle_t *hi2c, uint16_t memAddr, const uint8_t *pData, uint16_t length, uint32_t timeout)
{
    if(length > AT24C512B_PAGE_SIZE) return AT24C512B_ERROR;

    uint8_t buf[AT24C512B_PAGE_SIZE + 2];
    buf[0] = (uint8_t)(memAddr >> 8);
    buf[1] = (uint8_t)(memAddr & 0xFF);

    for(uint16_t i = 0; i < length; i++)
        buf[i + 2] = pData[i];

    // Send memory address + page data
    if(I2C_Master_Transmit(hi2c, AT24C512B_BASE_ADDR, buf, length + 2, I2C_STOP, timeout) != I2C_OK)
        return AT24C512B_ERROR;

    // Wait for EEPROM to finish writing
    if(I2C_IsDeviceReady(hi2c, AT24C512B_BASE_ADDR, 100, timeout) != I2C_OK)
        return AT24C512B_TIMEOUT;

    return AT24C512B_OK;
}

/* ===========================
   Read a single byte
   =========================== */
AT24C512B_Status_t AT24C512B_ReadByte(I2C_Handle_t *hi2c, uint16_t memAddr, uint8_t *data, uint32_t timeout)
{
    uint8_t addr[2];
    addr[0] = (uint8_t)(memAddr >> 8);
    addr[1] = (uint8_t)(memAddr & 0xFF);

    // Send memory address first (no stop)
    if(I2C_Master_Transmit(hi2c, AT24C512B_BASE_ADDR, addr, 2, I2C_REPEATED_START, timeout) != I2C_OK)
        return AT24C512B_ERROR;

    // Read single byte from EEPROM
    if(I2C_Master_Receive(hi2c, AT24C512B_BASE_ADDR, data, 1, I2C_STOP, timeout) != I2C_OK)
        return AT24C512B_ERROR;

    return AT24C512B_OK;
}

/* ===========================
   Read sequential bytes
   =========================== */
AT24C512B_Status_t AT24C512B_ReadSequential(I2C_Handle_t *hi2c, uint16_t memAddr, uint8_t *pData, uint16_t length, uint32_t timeout)
{
    uint8_t addr[2];
    addr[0] = (uint8_t)(memAddr >> 8);
    addr[1] = (uint8_t)(memAddr & 0xFF);

    // Send memory address first (no stop)
    if(I2C_Master_Transmit(hi2c, AT24C512B_BASE_ADDR, addr, 2, I2C_REPEATED_START, timeout) != I2C_OK)
        return AT24C512B_ERROR;

    // Read multiple bytes from EEPROM
    if(I2C_Master_Receive(hi2c, AT24C512B_BASE_ADDR, pData, length, I2C_STOP, timeout) != I2C_OK)
        return AT24C512B_ERROR;

    return AT24C512B_OK;
}
