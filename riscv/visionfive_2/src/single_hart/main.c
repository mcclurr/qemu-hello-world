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

static void uart_put_hex(uint64_t value)
{
    const char hex[] = "0123456789abcdef";

    for (int shift = 60; shift >= 0; shift -= 4) {
        uart_putchar(hex[(value >> shift) & 0xf]);
    }
}

static uint64_t read_sstatus(void)
{
    uint64_t value;

    __asm__ volatile (
        "csrr %0, sstatus"
        : "=r"(value)
    );

    return value;
}

void main(void)
{
    uart_puts("\r\nHello from my bare-metal RISC-V program!\r\n");

    uint64_t sstatus = read_sstatus();

    uart_puts("sstatus = 0x");
    uart_put_hex(sstatus);
    uart_puts("\r\n");

    while (1)
        ;
}