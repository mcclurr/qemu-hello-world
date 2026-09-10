CROSS = riscv-none-elf

CFLAGS = -march=rv64imac -mabi=lp64 \
         -ffreestanding -nostdlib \
         -Wall -Wextra -O0 -g

hello.elf: start.S main.c linker.ld
	$(CROSS)-gcc $(CFLAGS) \
		-T linker.ld \
		start.S main.c \
		-o hello.elf

hello.bin: hello.elf
	$(CROSS)-objcopy -O binary hello.elf hello.bin

clean:
	rm -f hello.elf hello.bin