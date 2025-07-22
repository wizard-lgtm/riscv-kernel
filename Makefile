# WARNING: THIS CODE IS AI GENERATED!
# I DON'T KNOW MAKE
# I ALSO HATE IT!

# Compile C source files (src directory)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Compile C source files (lib directory) 
$(BUILD_DIR)/lib/%.o: $(LIB_DIR)/%.c | $(BUILD_DIR)/lib
	$(CC) $(CFLAGS) -o $@ $# Compile C source files (src directory)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Compile C source files (lib directory) 
$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $# RISC-V Kernel Makefile

# Toolchain configuration
CC = riscv64-linux-gnu-gcc
AS = riscv64-linux-gnu-as
LD = riscv64-linux-gnu-ld
OBJDUMP = riscv64-linux-gnu-objdump
OBJCOPY = riscv64-linux-gnu-objcopy

# Directories
SRC_DIR = src
BUILD_DIR = build
LIB_DIR = $(SRC_DIR)/lib

# Include directories
INCLUDES = -I$(SRC_DIR) -I$(LIB_DIR)

# Compiler flags
CFLAGS = -c -nostdlib -nostartfiles -ffreestanding -Wall -Wextra -g $(INCLUDES)
ASFLAGS = 
LDFLAGS = -T $(SRC_DIR)/link.ld

# Auto-discover source files
C_SOURCES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIB_DIR)/*.c)
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.s)

# Object files - preserve directory structure
SRC_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(wildcard $(SRC_DIR)/*.c))
LIB_OBJECTS = $(patsubst $(LIB_DIR)/%.c,$(BUILD_DIR)/lib/%.o,$(wildcard $(LIB_DIR)/*.c))
ASM_OBJECTS = $(patsubst $(SRC_DIR)/%.s,$(BUILD_DIR)/%.o,$(ASM_SOURCES))
OBJECTS = $(ASM_OBJECTS) $(SRC_OBJECTS) $(LIB_OBJECTS)

# Target kernel
KERNEL = $(BUILD_DIR)/kernel.elf

# QEMU configuration
QEMU = qemu-system-riscv64
QEMU_FLAGS = -nographic -machine virt -kernel $(KERNEL)

# Default target
all: $(KERNEL)

# Build kernel
$(KERNEL): $(OBJECTS) | $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $@ $^
	@echo "Kernel built successfully: $@"

# Compile C source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR) $(BUILD_DIR)/lib
	$(CC) $(CFLAGS) -o $@ $<

# Compile library C files
$(BUILD_DIR)/lib/%.o: $(LIB_DIR)/%.c | $(BUILD_DIR) $(BUILD_DIR)/lib
	$(CC) $(CFLAGS) -o $@ $<

# Assemble assembly files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s | $(BUILD_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Create build directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/lib:
	mkdir -p $(BUILD_DIR)/lib

# Run kernel in QEMU
run: $(KERNEL)
	$(QEMU) $(QEMU_FLAGS)

# Run kernel in QEMU with debugging support
debug: $(KERNEL)
	$(QEMU) $(QEMU_FLAGS) -s -S

# Generate disassembly
disasm: $(KERNEL)
	$(OBJDUMP) -d $(KERNEL) > $(BUILD_DIR)/kernel.dis
	@echo "Disassembly generated: $(BUILD_DIR)/kernel.dis"

# Generate binary file
bin: $(KERNEL)
	$(OBJCOPY) -O binary $(KERNEL) $(BUILD_DIR)/kernel.bin
	@echo "Binary generated: $(BUILD_DIR)/kernel.bin"

# Show kernel size
size: $(KERNEL)
	@echo "Kernel size:"
	@ls -lh $(KERNEL)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	@echo "Build directory cleaned"

# Clean and rebuild
rebuild: clean all

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the kernel (default)"
	@echo "  run      - Build and run kernel in QEMU"
	@echo "  debug    - Build and run kernel with QEMU debugging"
	@echo "  disasm   - Generate disassembly listing"
	@echo "  bin      - Generate binary file"
	@echo "  size     - Show kernel file size"
	@echo "  clean    - Remove build artifacts"
	@echo "  rebuild  - Clean and rebuild"
	@echo "  help     - Show this help message"

# Declare phony targets
.PHONY: all run debug disasm bin size clean rebuild help

# Show variables (for debugging Makefile)
show-vars:
	@echo "CC = $(CC)"
	@echo "AS = $(AS)"
	@echo "LD = $(LD)"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"
	@echo "C_SOURCES = $(C_SOURCES)"
	@echo "ASM_SOURCES = $(ASM_SOURCES)"
	@echo "OBJECTS = $(OBJECTS)"
	@echo "KERNEL = $(KERNEL)"