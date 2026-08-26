#include "uart.h"
#include "boot.h"
#include "commands.h"

int main(void)
{
    uart_init();

    uart_puts("\r\n");
    uart_puts("Bootloader starting...\r\n");
    uart_puts("Press 'b' to enter bootloader.\r\n");
    uart_puts("Press anything else to boot application.\r\n");
    uart_puts("> ");

    char command = uart_getchar();

    uart_putchar(command);
    uart_puts("\r\n");

    if (command == 'b') {
        command_loop();
    }

    uart_puts("Booting application...\r\n");
    jump_to_application();
}