CROSS_COMPILE := arm-none-eabi-

CC      := $(CROSS_COMPILE)gcc
OBJDUMP := $(CROSS_COMPILE)objdump
SIZE    := $(CROSS_COMPILE)size

CPUFLAGS := \
	-mcpu=cortex-m3 \
	-mthumb

CFLAGS := \
	$(CPUFLAGS) \
	-Wall \
	-Wextra \
	-O0 \
	-g3 \
	-ffreestanding \
	-fno-builtin \
	-ffunction-sections \
	-fdata-sections

LDFLAGS := \
	$(CPUFLAGS) \
	-T linker.ld \
	-nostdlib \
	-Wl,--gc-sections \
	-Wl,-Map=hello.map

SOURCES := startup.S main.c
TARGET  := hello.elf

.PHONY: all run debug inspect clean

all: $(TARGET)

$(TARGET): $(SOURCES) linker.ld
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o $@
	$(SIZE) $@

run: $(TARGET)
	qemu-system-arm \
		-machine stm32vldiscovery \
		-kernel $(TARGET) \
		-nographic

debug: $(TARGET)
	qemu-system-arm \
		-machine stm32vldiscovery \
		-kernel $(TARGET) \
		-nographic \
		-S \
		-gdb tcp::1234

inspect: $(TARGET)
	$(OBJDUMP) -h -d $(TARGET)

clean:
	rm -f $(TARGET) hello.map