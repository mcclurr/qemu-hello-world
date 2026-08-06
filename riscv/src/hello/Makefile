CC = riscv-none-elf-gcc

BUILD_DIR = build

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

TARGET = $(BUILD_DIR)/hello.elf

OBJS = \
	$(BUILD_DIR)/startup.o \
	$(BUILD_DIR)/main.o

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/startup.o: startup.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) linker.ld
	$(CC) $(CFLAGS) $(LDFLAGS) \
		$(OBJS) \
		-o $@

run: $(TARGET)
	qemu-system-riscv32 \
		-machine virt \
		-bios none \
		-kernel $(TARGET) \
		-nographic

debug: $(TARGET)
	qemu-system-riscv32 \
		-machine virt \
		-bios none \
		-kernel $(TARGET) \
		-nographic \
		-S \
		-gdb tcp::1234

clean:
	rm -rf $(BUILD_DIR)