# 🚗 Smart Car Parking System (STM32F103)

<p align="left">
  <img src="https://shields.io" alt="MCU">
  <img src="https://shields.io" alt="Architecture">
  <img src="https://shields.io" alt="Language">
  <img src="https://shields.io" alt="Compiler">
  <img src="https://shields.io" alt="License">
</p>

An advanced, highly modular Embedded Systems project designed to automate and manage a smart car parking lot using the **STM32F103C6** (ARM Cortex-M3) microcontroller. The system features dynamic gate control, non-volatile state logging, and safe peripheral drivers written completely from scratch (MCAL/ECUAL layered architecture).

---

## 📸 System Overview & Circuit

### System Hardware Architecture
Below is the hardware connections and interfacing schematic for the parking system peripherals:

<p align="center">
  <img src="Docs/Circuit.png" alt="Smart Parking Circuit Diagram" width="800">
</p>

---

## 🏗️ Architectural Layering (Full System Breakdown)

The firmware is designed using a strictly decoupled, layered layered architecture to separate application logic from low-level register manipulations. Below is the comprehensive map of all modules included in the repository:

```mermaid
graph TD
    APP[Application Layer: App.c / MCU_Config.h] --> ECUAL[ECU Abstraction Layer]
    ECUAL --> MCAL[Microcontroller Abstraction Layer]
    MCAL --> HW[STM32F103C6 Hardware Core]

    subgraph ECUAL [ECU Peripheral Drivers]
        BUTTON[Button Driver]
        KEYPAD[KeyPad Driver]
        LCD[LCD Display Driver]
        SERVO[Servo Motor Driver]
        LED[LED Status Driver]
        EEPROM[EEPROM AT24C512B]
    end

    subgraph MCAL [Microcontroller Core Drivers]
        RCC[RCC Clock Driver]
        GPIO[GPIO Core Driver]
        EXTI[Interrupt Core Driver]
        TIMER[Timer Driver]
        UART[UART Communication]
        I2C[I2C Master/Slave]
        SPI[SPI Protocol Driver]
    end
```

### 📂 Repository File Structure
```directory
├── Core/
│   ├── APP/
│   │   ├── App.c
│   │   └── MCU_Config.h
│   ├── ECUAL/
│   │   ├── Button_Driver/
│   │   ├── EEPROM_Driver/
│   │   ├── KeyPad_Driver/
│   │   ├── LCD_Driver/
│   │   ├── Led_Driver/
│   │   └── ServoMotor_Driver/
│   ├── MCAL/
│   │   ├── GPIO_Driver/
│   │   ├── I2C_Driver/
│   │   ├── Interrupt_Driver/
│   │   ├── RCC_Driver/
│   │   ├── SPI_Driver/
│   │   ├── Timer_Driver/
│   │   └── UART_Driver/
│   └── Utilities/
└── Docs/
    ├── Circuit.png
    └── ControlFlow-main.png
```

---

## ⚙️ Peripheral Integration Details (MCAL)

* **RCC Clock Driver:** Dynamically decodes `RCC->CFGR` to calculate system core frequencies ($16\text{ MHz}$ HSI / $8\text{ MHz}$ HSE), automatically adjustments clock propagation across AHB, APB1, and APB2 buses.
* **GPIO Core Driver:** Manages atomic bit manipulation and handles full custom mode configurations (Analog, Input Floating, Pull-Up/Down, Push-Pull, and Open-Drain outputs).
* **Interrupt Driver (EXTI):** Handles hardware event-triggered interrupts (such as sensor triggers or emergency bounds).
* **Timer Driver:** Generates hardware precise PWM outputs to drive gate positioning smoothly.
* **UART Driver:** Custom asynchronous communication module featuring automatic Baudrate calculation utilizing active bus frequency polling APIs.
* **I2C Driver:** Master/Slave protocol implementation optimized for byte-stream safety constraints, preventing runtime data corruption on transmission frames.
* **SPI Driver:** Custom synchronous serial peripheral interface designed for high-speed local data bus extensions.

---

## 🎛️ Human-Machine Interface & Actuators (ECUAL)

| Module Driver | Protocol / Connection | Architectural Function |
| :--- | :--- | :--- |
| **KeyPad Driver** | Matrix GPIO Scanning | Captures security passcodes and administrative gate override commands. |
| **LCD Display Driver** | Digital Parallel Interface | Renders live telemetry, available slot counts, and interactive system diagnostics. |
| **Button Driver** | Debounced GPIO Input | Acts as manual entry/exit request interfaces. |
| **Servo Motors** | Timer PWM Modulation | Direct mechanical operation of security entry and exit barriers ($0^{\circ}$ to $90^{\circ}$). |
| **EEPROM AT24C512B** | Master I2C Interface | Retains dynamic structural stats and logging states over non-volatile safe blocks. |
| **LED Indicators** | Configurable GPIO Output | Immediate physical visualization for Active-High / Active-Low barrier alerts. |

---

## 📊 Application Flow Chart

The system operates based on deterministic event polling and structural state flags. The execution loop lifecycle proceeds as follows:

<p align="center">
  <img src="Docs/ControlFlow-main.png" alt="Application Control Flow" width="550">
</p>

### Detailed Event Execution State
```mermaid
stateDiagram-v2
    [*] --> HW_Initialization : Power On
    HW_Initialization --> Peripheral_Verification : Init Drivers (RCC, GPIO, I2C, SPI, Timers)
    Peripheral_Verification --> Idle_State : Load Parking State from EEPROM
    
    Idle_State --> Security_Check : Admin KeyPad / Button Input Received
    Security_Check --> Verify_Slots : Credentials Approved
    
    Verify_Slots --> Gate_Opening : Slot Available -> Print LCD Update
    Verify_Slots --> Idle_State : Parking Full -> Flash Alarm LED
    
    Gate_Opening --> Vehicle_Passing : Drive Servo to 90°
    Vehicle_Passing --> Gate_Closing : Clear Sensor Boundary
    Gate_Closing --> Sync_Storage : Reset Servo to 0° -> Commit State to EEPROM
    Sync_Storage --> Idle_State
```

---

## 🚀 Getting Started & Build Instructions

### Prerequisites
* **Development Environment:** [STM32CubeIDE](https://st.com) (Tested on Version 2.0.0+)
* **Toolchain:** `arm-none-eabi-gcc` (v13.3.1)
* **Hardware Setup:** STM32F103C6 Dev Board (BluePill) + ST-Link V2 Debugger.

### Compiling from Source
1. Clone the repository into your workspace directory:
   ```bash
   git clone https://github.com
   ```
2. Open STM32CubeIDE, choose **File -> Import -> Existing Projects into Workspace** and select the cloned directory.
3. Clean the project to ensure object list consistency:
   `Project -> Clean...`
4. Trigger the GNU Make compiler using the **Build (Hammer Icon)** or via shortcut `Ctrl + B`.
5. The build chain outputs can be verified in the Console tab:
   ```bash
   arm-none-eabi-gcc -gdwarf-2 -o "Full_Project_2.elf" @"objects.list" -mcpu=cortex-m3 ...
   Build Finished. 0 errors, 0 warnings.
   ```

---

## 🛠️ Future Roadmap Enhancements
- [ ] Integration of a custom lightweight RTOS Scheduler for multi-tasking.
- [ ] Enhancing I2C handling via asynchronous non-blocking interrupts.
- [ ] Multi-zone tracking optimization algorithms.

---

## 📄 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 👨‍💻 Author
**Mahmoud Saleh**
* Embedded Systems Engineer
* [GitHub Profile](https://github.com/Mahmoud976)
* [LinkedIn Profile](https://linkedin.com)
