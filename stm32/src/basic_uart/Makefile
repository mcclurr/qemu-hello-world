CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

CFLAGS  = -mcpu=cortex-m4 -mthumb -O0 -g3 -Wall -Wextra
LDFLAGS = -T linker.ld -nostdlib -Wl,-Map=build/hello.map

BUILD_DIR = build
TARGET    = $(BUILD_DIR)/hello.elf

SRCS = startup.S main.c
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
OBJS := $(OBJS:%.S=$(BUILD_DIR)/%.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)