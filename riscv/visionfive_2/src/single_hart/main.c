#include <stdint.h>

#define UART_BASE 0x10000000UL

#define UART_THR (*(volatile uint32_t *)(UART_BASE + 0x00))
#define UART_LSR (*(volatile uint32_t *)(UART_BASE + 0x14))

#define UART_LSR_THRE (1 << 5)

static void uart_putchar(char c)
{
    while (!(UART_LSR & UART_LSR_THRE))
        ;

    UART_THR = c;
}

static void uart_puts(const char *s)
{
    while (*s)
        uart_putchar(*s++);
}

void main(void)
{
    uart_puts("\r\nHello from my bare-metal RISC-V program!\r\n");

    while (1)
        ;
}