#include <stdint.h>

#define UART_BASE 0x10000000UL

#define UART_THR (*(volatile uint32_t *)(UART_BASE + 0x00))
#define UART_LSR (*(volatile uint32_t *)(UART_BASE + 0x14))

#define UART_LSR_THRE (1 << 5)

/* SBI Hart State Management extension */
#define SBI_EXT_HSM        0x48534D
#define SBI_HART_START     0

struct sbiret {
    long error;
    long value;
};

extern void _secondary_start(void);

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

static void uart_put_uint(uint64_t value)
{
    char buf[20];
    int i = 0;

    if (value == 0) {
        uart_putchar('0');
        return;
    }

    while (value > 0) {
        buf[i++] = '0' + (value % 10);
        value /= 10;
    }

    while (i > 0)
        uart_putchar(buf[--i]);
}

static void uart_put_int(long value)
{
    if (value < 0) {
        uart_putchar('-');
        value = -value;
    }

    uart_put_uint((uint64_t)value);
}

static struct sbiret sbi_call(
    unsigned long eid,
    unsigned long fid,
    unsigned long arg0,
    unsigned long arg1,
    unsigned long arg2)
{
    register unsigned long a0 asm("a0") = arg0;
    register unsigned long a1 asm("a1") = arg1;
    register unsigned long a2 asm("a2") = arg2;
    register unsigned long a6 asm("a6") = fid;
    register unsigned long a7 asm("a7") = eid;

    asm volatile (
        "ecall"
        : "+r"(a0), "+r"(a1)
        : "r"(a2), "r"(a6), "r"(a7)
        : "memory"
    );

    struct sbiret ret = {
        .error = (long)a0,
        .value = (long)a1
    };

    return ret;
}

static struct sbiret sbi_hart_start(
    unsigned long hartid,
    unsigned long start_addr,
    unsigned long opaque)
{
    return sbi_call(
        SBI_EXT_HSM,
        SBI_HART_START,
        hartid,
        start_addr,
        opaque
    );
}

void secondary_main(uint64_t hart_id)
{
    uart_puts("Hello from secondary hart ");
    uart_put_uint(hart_id);
    uart_puts("!\r\n");

    while (1)
        ;
}

void main(void)
{
    uart_puts("\r\nHello from boot hart 1!\r\n");
    uart_puts("About to start hart 2...\r\n");

    sbi_hart_start(
        2,
        (unsigned long)_secondary_start,
        0
    );

    while (1)
        ;
}