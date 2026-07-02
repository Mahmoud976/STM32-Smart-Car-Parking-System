# TECHNICAL PROJECT REPORT: SMART CAR PARKING SYSTEM
**Automated Embedded Parking Management Infrastructure using STM32F103C6**

---

## 1. EXECUTIVE SUMMARY
This report details an automated Smart Car Parking System designed using STM32F103C6 (ARM Cortex-M3). The system features register-level C programming for optimized performance, featuring gate control, security passcodes, live LCD telemetry, and EEPROM state logging.

---

## 2. HARDWARE SPECIFICATIONS
*   **MCU:** STM32F103C6 (72 MHz).
*   **HMI:** 16x2 LCD & 4x4 Matrix Keypad.
*   **Actuators:** Servo Motors (PWM-driven).
*   **Storage/Logs:** AT24C512B EEPROM (I2C) & UART Terminal.
*   **Simulation:** Labcenter Proteus.

---

## 3. SOFTWARE ARCHITECTURE
A modular, layered approach is used:
*   **Application Layer:** Main loop and Finite State Machine (FSM).
*   **ECU Abstraction Layer (ECUAL):** Drivers for LCD, Keypad, Servos, EEPROM.
*   **Microcontroller Abstraction Layer (MCAL):** Register-level drivers (RCC, GPIO, I2C, UART).

---

## 4. KEY FEATURES (MCAL)
*   **Clock/GPIO:** Optimized RCC and GPIO configuration.
*   **Communication:** I2C for EEPROM and UART for diagnostics.
*   **Control:** Timer-driven PWM for servo positioning.

---

## 5. PROJECT STRUCTURE
```directory
Smart-Car-Parking-System/
├── Core/ (APP, ECUAL, MCAL)
├── Src/ (main.c, syscalls.c)
├── Startup/ (Linker Script)
├── Proteus/ (Simulation)
└── README.md
```

---

## 6. APPLICATION CONTROL FLOW
The system operates via an event-driven state machine:
`Power On -> Init -> Idle -> Security Check -> Gate Control -> EEPROM Sync`.

---

## 7. ENGINEERING HIGHLIGHTS (v1.1.0)
*   Resolved linker errors in `UART_Init`.
*   Fixed C-standard assignment bugs in `Led_Init`.
*   Implemented strict pointer casting for memory stability.

---
**Compiled By:** Mahmoud Saleh | **Role:** Embedded Systems Engineer | **Version:** `v1.1.0`
