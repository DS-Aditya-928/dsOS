# dsOS - Minimal Operating System for ESP32

## Overview
**dsOS** is a lightweight operating system built entirely from scratch for the **ESP32 microcontroller**.  
dsOS does not rely on ESP-IDF or even stdlib, I built/am building that stuff myself.

This project demonstrates OS fundamentals on constrained hardware, with a total footprint of **5.9 KB**.

---

## Features
- **Cooperative Scheduler** – Basic multitasking with a round-robin co-operative scheduler  
- **Custom Memory Management** –  `malloc` implementation  
- **Peripheral Drivers** – UART, SPI, I2C, and GPIO support   
- **Lightweight Build** – <10kb binary size

---

## Tech Stack
- **Languages:** C, C++ (still porting parts out of C :p)  
- **Low-Level:** Xtensa Assembly, Linker Scripts  
- **Platform:** ESP32

---

## Getting Started

### Prerequisites
- Xtensa GCC toolchain installed (`xtensa-esp32-elf-g++`)
- [esptool.py](https://github.com/espressif/esptool) for flashing  
- ESP32 development board

### Build & Flash
1. Clone the repository:
   ```bash
   git clone https://github.com/DS-Aditya-928/dsOS.git
   cd dsOS
   ```
2. Build with your toolchain:
   ```bash
   make
   ```

   This will spit out an elf and a bin. The elf is an intermediate, the bin is what's actually flashed.

3. Flash:
   ```bash
   esptool.py --chip esp32 --port "PORT HERE" --before default_reset --after hard_reset write_flash 0x1000 os.bin
   ```

Alternative Build and flash:
   ```bash
   make flash
   ```
   Note: I set this up for my comedy dev environment where I've got a WSL2 Ubuntu machine for compilation but still use the host to actually upload code. If you're normal and use Linux you'll need to change this command in the makefile around a lil bit.
---

## Usage
Once flashed, connect to the ESP32 over serial (I use PuTTY) and access the built-in shell.  
From here, you can test drivers, and observe task scheduling.

---

## Roadmap
- [x] STOP CALLING THE OS A BOOTLOADER (this is a quirk of where the OS resides in memory, it sits where the stage 2 bootloader used to be.)
- [ ] Add preemptive scheduling option  
- [ ] Expand shell commands  
- [ ] Add lightweight filesystem support  

---

## License
Super duper proprietary DS License. See [LICENSE](./LICENSE) for details.
