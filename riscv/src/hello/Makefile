CC = riscv-none-elf-gcc

CFLAGS = \
	-march=rv32imac \
	-mabi=ilp32 \
	-Wall \
	-Wextra \
	-O0 \
	-g \
	-ffreestanding \
	-nostdlib

LDFLAGS = -T linker.ld

all: hello.elf

hello.elf: startup.S main.c linker.ld
	$(CC) $(CFLAGS) $(LDFLAGS) \
		startup.S \
		main.c \
		-o $@

run: hello.elf
	qemu-system-riscv32 \
		-machine virt \
		-bios none \
		-kernel hello.elf \
		-nographic

debug: hello.elf
	qemu-system-riscv32 \
		-machine virt \
		-bios none \
		-kernel hello.elf \
		-nographic \
		-S \
		-gdb tcp::1234

clean:
	rm -f hello.elf