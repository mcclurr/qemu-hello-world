#include "commands.h"
#include "uart.h"
#include "boot.h"

static void print_help(void)
{
    uart_puts("\r\nCommands:\r\n");
    uart_puts("  h - help\r\n");
    uart_puts("  i - application info\r\n");
    uart_puts("  b - boot application\r\n");
}

static void print_info(void)
{
    uart_puts("\r\nApplication address: 0x08008000\r\n");
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

        default:
            uart_puts("Unknown command. Press 'h' for help.\r\n");
            break;
        }
    }
}