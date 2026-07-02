# 📜 Changelog

All notable changes to the **Smart Car Parking System** project will be documented in this file. The format is based on [Keep a Changelog](https://keepachangelog.com).

---

## - 2026-07-02

### 🚀 Added
* Added **Proteus hardware simulation design file** (`Smart_Car_Parking_System.pdsprj`) to the root directory for interactive debugging.
* Implemented strict `const uint8_t *` type validation inside the `I2C_Slave_Transmit` handler across both `.h` and `.c` layers to guard master transmission memory boundaries.
* Re-architected the `Led_Init` compilation routine, replacing unstable nested ternary operations with safe direct assignment expressions.

### 🐛 Fixed
* Fixed a critical **Linker Error (Undefined Reference)** inside `UART_Init` caused by a typo in the clock tracking methods (`RCC_Get_PLCK1Freq` and `RCC_Get_PLCK2Freq` were renamed to `RCC_Get_PCLK1Freq` and `RCC_Get_PCLK2Freq`).
* Resolved explicit compiler warnings (`lvalue required` and `pointer mismatch`) regarding the variable casting syntax during sequential `GPIO_ReadPin` reads.

---

## - 2026-06-15

### 🏗️ Added
* Initial baseline release of the Smart Parking system firmware core.
* Full customized register-level **MCAL Drivers layer** (`RCC`, `GPIO`, `UART`, `I2C`, `SPI`, `Timer`, `EXTI`).
* **ECUAL Drivers layer** implementation supporting integrated hardware peripherals (`LCD 16x2`, `Matrix KeyPad`, `Servo Motor`, `EEPROM AT24C512B`).
* Sequential system logic loop handling secure parking capacity bounds and automatic gate servo control.
