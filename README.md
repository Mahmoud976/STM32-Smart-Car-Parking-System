# Smart Car Parking System (STM32F103)

[![License: MIT](https://shields.io)](LICENSE)

An advanced, highly modular Embedded Systems project designed to automate and manage a smart car parking lot using the **STM32F103C6** (ARM Cortex-M3) microcontroller. The system features dynamic gate control, non-volatile state logging, and safe peripheral drivers written completely from scratch using an MCAL/ECUAL layered architecture.

---

## System Overview & Simulation

### System Hardware Architecture
Below is the hardware connections and interfacing schematic for the parking system peripherals. You can run the live design using the Proteus simulation files located inside the `Proteus/` directory.

<p align="center">
  <img src="Docs/Circuit.png" alt="Smart Parking Circuit Diagram" width="800">
</p>

---

## Architectural Layering (Full System Breakdown)

The firmware is designed using a strictly decoupled, layered architecture to separate application logic from low-level register manipulations. Below is the comprehensive map of all modules included in the repository:

```mermaid
graph TD
    APP[Application Layer: Core/APP/ & Src/main.c] --> ECUAL[ECU Abstraction Layer]
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

### Repository File Structure
```directory
Smart-Car-Parking-System/
│
├── Core/                              # Core Project Configurations & Drivers
│   ├── APP/                           # Application Configurations (MCU_Config.h)
│   ├── ECUAL/                         # ECU Abstraction Layer (Button, KeyPad, LCD, Servo, LED, EEPROM)
│   ├── MCAL/                          # Microcontroller Abstraction Layer (GPIO, I2C, EXTI, RCC, SPI, Timer, UART)
│   └── Utilities/                     # Shared standard types and helper macros
│
├── Src/                               # Main Application Source Files
│   ├── main.c                         # Main program execution loop & logic
│   ├── syscalls.c                     # Low-level system calls for ARM GCC compiler
│   └── sysmem.c                       # System memory management & heap allocation
│
├── Startup/                           # Device Boot Sequence & Memory Linker Scripts
│   ├── startup_stm32f103c6tx.s        # Assembly startup file (Vector table & Reset handler)
│   └── STM32F103C6TX_FLASH.ld         # Linker script for Flash & RAM memory mapping
│
├── Proteus/                           # Contains the hardware simulation design files
├── Docs/                              # System documentation images (Circuit, Flowcharts)
├── CHANGELOG.md                       # Comprehensive version tracking history log
├── LICENSE                            # MIT Open-Source Legal License text
└── README.md                          # This Project Documentation file
```

---

## Peripheral Integration Details (MCAL)

* **RCC Clock Driver:** Dynamically decodes `RCC->CFGR` to calculate system core frequencies ($16\text{ MHz}$ HSI / $8\text{ MHz}$ HSE), automatically adjusting clock propagation across AHB, APB1, and APB2 buses.
* **GPIO Core Driver:** Manages atomic bit manipulation and handles full custom mode configurations (Analog, Input Floating, Pull-Up/Down, Push-Pull, and Open-Drain outputs).
* **Interrupt Driver (EXTI):** Handles hardware event-triggered interrupts (such as sensor triggers or emergency bounds).
* **Timer Driver:** Generates hardware-precise PWM outputs to drive gate positioning smoothly.
* **UART Driver:** Custom asynchronous communication module featuring automatic Baudrate calculation utilizing active bus frequency polling APIs.
* **I2C Driver:** Master/Slave protocol implementation optimized for byte-stream safety constraints, preventing runtime data corruption on transmission frames.
* **SPI Driver:** Custom synchronous serial peripheral interface designed for high-speed local data bus extensions.

---

## Human-Machine Interface & Actuators (ECUAL)

| Module Driver | Protocol / Connection | Architectural Function |
| :--- | :--- | :--- |
| **KeyPad Driver** | Matrix GPIO Scanning | Captures security passcodes and administrative gate override commands. |
| **LCD Display Driver** | Digital Parallel Interface | Renders live telemetry, available slot counts, and interactive system diagnostics. |
| **Button Driver** | Debounced GPIO Input | Acts as manual entry/exit request interfaces. |
| **Servo Motors** | Timer PWM Modulation | Direct mechanical operation of security entry and exit barriers ($0^{\circ}$ to $90^{\circ}$). |
| **EEPROM AT24C512B** | Master I2C Interface | Retains dynamic structural stats and logging states over non-volatile safe blocks. |
| **LED Indicators** | Configurable GPIO Output | Immediate physical visualization for Active-High / Active-Low barrier alerts. |

---

## Application Flow Chart

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

## Changelog
See the comprehensive release history, bug fixes, and development iterations in the [CHANGELOG.md](CHANGELOG.md) file.

---

## Getting Started & Build Instructions

### Prerequisites
* **Development Environment:** [STM32CubeIDE](https://st.com) (Tested on Version 2.0.0+)
* **Simulation Software:** Proteus Design Suite (for running files inside `Proteus/`)
* **Toolchain:** `arm-none-eabi-gcc` (v13.3.1)

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

## Future Roadmap Enhancements
- [ ] Integration of a custom lightweight RTOS Scheduler for multi-tasking.
- [ ] Enhancing I2C handling via asynchronous non-blocking interrupts.
- [ ] Multi-zone tracking optimization algorithms.

---

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## Author
**Mahmoud Saleh**
* Embedded Systems Engineer
* [GitHub Profile](https://github.com/Mahmoud976)
* [LinkedIn Profile](https://linkedin.com)
