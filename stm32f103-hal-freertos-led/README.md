# DEMO-STM32

## stm32f103-hal-freertos-led

**Hardware Platform**

- STM32F103 "BluePill"
  - STM32F103C8T6
  - ARM Cortex-M3 32-bit RISC
  - 20 kB RAM
  - 64 kB ROM/Flash

**Software Platform**

- IDE
  - Eclipse 2022-09 (4.25.0), build 20220908-1902
  - STM32CubeMX
- Compiler
  - ARM GNU GCC
- Language
  - C
- Frameworks
  - STM32-HAL
- Operation System
  - FreeRTOS

**Build modes**

- Release
  - code, init.data > FLASH
  - other data > RAM, CMRAM
- Debug
  - all > RAM

**Clock Configuration**

| HSE   | SYSCLK | HCLK   | APB1.PCLK | APB1.TCLK | APB2.PCLK | APB2.TCLK |
|-------|--------|--------|-----------|-----------|-----------|-----------|
| 8MHz  | 72MHz  | 72MHz  | 36MHz     | 72MHz     | 72MHz     | 72MHz     |

**Project**

- SysTick IRQ-handler
  - FreeRTOS scheduller tick

- LED_USER_RTOS_Task
  - LED_USER.toggle by software timer
