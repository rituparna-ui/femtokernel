# Cross-compiler
CC = aarch64-linux-gnu-gcc
AS = aarch64-linux-gnu-as
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy

# Flags
CFLAGS = -ffreestanding -nostdlib -nostartfiles -O2
ASFLAGS =
LDFLAGS = -nostdlib

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
ASM_SOURCES = $(SRC_DIR)/boot.S
C_SOURCES = $(SRC_DIR)/kernel.c

# Object files
ASM_OBJECTS = $(BUILD_DIR)/boot.o
C_OBJECTS = $(BUILD_DIR)/kernel.o

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

clean:
	rm -rf $(BUILD_DIR)

sync:
	sudo cp build/kernel8.img /media/rituu/bootfs/kernel8.img

.PHONY: all clean