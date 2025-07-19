# Cross-compiler
CC = aarch64-linux-gnu-gcc
AS = aarch64-linux-gnu-as
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy

# Flags
CFLAGS = -ffreestanding -nostdlib -nostartfiles -O2 -Isrc
ASFLAGS =
LDFLAGS = -nostdlib

# Directories
SRC_DIR = src
LIB_DIR = $(SRC_DIR)/lib
BUILD_DIR = build

# Source files
ASM_SOURCES = $(SRC_DIR)/boot.S
C_SOURCES = $(SRC_DIR)/kernel.c $(LIB_DIR)/gpio.c $(LIB_DIR)/uart.c

# Object files
ASM_OBJECTS = $(BUILD_DIR)/boot.o
C_OBJECTS = $(BUILD_DIR)/kernel.o $(BUILD_DIR)/gpio.o $(BUILD_DIR)/uart.o

# Target
TARGET = $(BUILD_DIR)/kernel8.img

all: $(TARGET)

$(TARGET): $(ASM_OBJECTS) $(C_OBJECTS)
	$(LD) $(LDFLAGS) -T linker.ld $(ASM_OBJECTS) $(C_OBJECTS) -o $(BUILD_DIR)/kernel.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)/kernel.elf $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	mkdir -p $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

sync:
	sudo cp build/kernel8.img /media/rituu/bootfs/kernel8.img

.PHONY: all clean
