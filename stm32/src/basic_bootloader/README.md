# STM32F446RE Tiny Bootloader Example

Flash layout:
- Bootloader: 0x08000000 - 0x08007FFF (32 KiB)
- Application: starts at 0x08008000

Build both images:

    make

Generated ELF files:

    bootloader/build/bootloader.elf
    application/build/application.elf

Flash both ELFs. The bootloader runs after reset, prints a message over USART2, relocates VTOR to the application's vector table, loads the application's initial MSP, and branches to the application's Reset_Handler.

Expected UART output at 115200 baud:

    Hello from bootloader!
    Hello from application!
