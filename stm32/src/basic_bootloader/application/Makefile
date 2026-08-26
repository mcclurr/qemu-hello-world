CROSS_COMPILE := arm-none-eabi-
CC      := $(CROSS_COMPILE)gcc
OBJDUMP := $(CROSS_COMPILE)objdump
SIZE    := $(CROSS_COMPILE)size
OBJCOPY := $(CROSS_COMPILE)objcopy

BUILD_DIR := build

BIN := $(BUILD_DIR)/application.bin

CPUFLAGS := -mcpu=cortex-m4 -mthumb

CFLAGS := $(CPUFLAGS) -Wall -Wextra -O0 -g3 -ffreestanding -fno-builtin -ffunction-sections -fdata-sections

LDFLAGS := $(CPUFLAGS) -T linker.ld -nostdlib -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/application.map

TARGET := $(BUILD_DIR)/application.elf

OBJS := $(BUILD_DIR)/startup.o $(BUILD_DIR)/main.o

.PHONY: all inspect clean

all: $(TARGET) $(BIN)

$(BIN): $(TARGET)
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/startup.o: startup.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) linker.ld
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $@

inspect: $(TARGET)
	$(OBJDUMP) -h -d $(TARGET)

clean:
	rm -rf $(BUILD_DIR)
