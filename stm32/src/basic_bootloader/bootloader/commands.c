#include "commands.h"
#include "uart.h"
#include "boot.h"
#include "flash.h"

static void print_help(void)
{
    uart_puts("\r\nCommands:\r\n");
    uart_puts("  h - help\r\n");
    uart_puts("  i - application info\r\n");
    uart_puts("  b - boot application\r\n");
    uart_puts("  e - erase application\r\n");
}

static void print_info(void)
{
    uint32_t app_stack = boot_get_app_stack();
    uint32_t app_reset = boot_get_app_reset();

    uart_puts("\r\nApplication address: ");
    uart_puthex32(APP_ADDR);

    uart_puts("\r\nInitial MSP:         ");
    uart_puthex32(app_stack);

    uart_puts("\r\nReset handler:       ");
    uart_puthex32(app_reset);

    uart_puts("\r\nApplication valid:   ");

    if (boot_application_is_valid()) {
        uart_puts("YES\r\n");
    } else {
        uart_puts("NO\r\n");
    }
}

void command_loop(void)
{
    uart_puts("\r\nEntered bootloader mode.\r\n");
    print_help();

    while (1) {
        uart_puts("\r\n> ");

        char command = uart_getchar();

        /* Echo what the user typed. */
        uart_putchar(command);
        uart_puts("\r\n");

        switch (command) {
        case 'h':
            print_help();
            break;

        case 'i':
            print_info();
            break;

        case 'b':
            if (boot_application_is_valid()) {
                uart_puts("Booting application...\r\n");
                jump_to_application();
            } else {
                uart_puts("Application invalid. Refusing to boot.\r\n");
            }
            break;

        case 'e':
            uart_puts("WARNING: erase application? Press 'y' to confirm.\r\n");
            uart_puts("> ");

            char confirm = uart_getchar();
            uart_putchar(confirm);
            uart_puts("\r\n");

            if (confirm != 'y') {
                uart_puts("Erase cancelled.\r\n");
                break;
            }

            uart_puts("Erasing application...\r\n");

            if (flash_erase_application() == 0) {
                uart_puts("Application erased.\r\n");
            } else {
                uart_puts("Flash erase FAILED.\r\n");
            }

            break;

        default:
            uart_puts("Unknown command. Press 'h' for help.\r\n");
            break;
        }
    }
}