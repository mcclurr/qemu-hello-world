#include <stdint.h>

#include "update.h"
#include "uart.h"
#include "flash.h"
#include "boot.h"

#define APP_MAX_SIZE (0x08080000UL - APP_ADDR)

int receive_firmware(void)
{
    uart_puts("Send firmware size...\r\n");

    uint32_t size = uart_get_u32();

    if (size == 0 || size > APP_MAX_SIZE) {
        uart_puts("Invalid firmware size.\r\n");
        return -1;
    }

    uart_puts("Erasing application...\r\n");

    if (flash_erase_application() != 0) {
        uart_puts("Erase failed.\r\n");
        return -1;
    }

    /*
     * Tell the PC that erase is complete and we're
     * actually ready for the binary now.
     */
    uart_puts("READY\r\n");

    uint32_t address = APP_ADDR;
    uint32_t bytes_received = 0;

    while (bytes_received < size) {
        uint32_t word = 0xFFFFFFFFUL;

        for (uint32_t i = 0; i < 4; i++) {
            if (bytes_received < size) {
                uint8_t byte = (uint8_t)uart_getchar();

                word &= ~(0xFFUL << (i * 8));
                word |= ((uint32_t)byte << (i * 8));

                bytes_received++;
            }
        }

        if (flash_program_word(address, word) != 0) {
            uart_puts("Programming failed.\r\n");
            return -1;
        }

        address += 4;
    }

    uart_puts("Programming complete.\r\n");

    if (!boot_application_is_valid()) {
        uart_puts("Application invalid after programming.\r\n");
        return -1;
    }

    uart_puts("Application valid.\r\n");
    uart_puts("OK\r\n");

    return 0;
}