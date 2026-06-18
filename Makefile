# ============================================================
# janOS Makefile
# Builds a 32-bit x86 kernel and boots it with GRUB/Multiboot
# ============================================================


# ------------------------------------------------------------
# Tools
# ------------------------------------------------------------

# C compiler used to compile both C files and .S assembly files
CC := gcc

# Linker used to create the final kernel ELF file
LD := ld

# Emulator used to run the operating system
QEMU := qemu-system-i386

# Tool used to create a bootable GRUB ISO image
GRUB_MKRESCUE := grub-mkrescue


# ------------------------------------------------------------
# Compiler and linker flags
# ------------------------------------------------------------

# Compiler flags:
# -m32                 build 32-bit x86 code
# -Wall -Wextra        enable useful warnings
# -O2                  optimize the code
# -g                   include debug information
# -ffreestanding       compile without assuming a hosted C environment
# -nostdlib            do not use the standard C library
# -nostartfiles        do not use normal C startup files
# -fno-pie             do not generate position-independent executable code
# -fno-stack-protector disable stack protector runtime dependencies
CFLAGS := -m32 \
          -Wall -Wextra \
          -O2 -g \
          -ffreestanding \
          -nostdlib \
          -nostartfiles \
          -fno-pie \
          -fno-stack-protector

# Linker flags:
# -m elf_i386          create a 32-bit x86 ELF file
# -T linker.ld         use our custom linker script
LDFLAGS := -m elf_i386 \
           -T linker.ld


# ------------------------------------------------------------
# Directories
# ------------------------------------------------------------

# Source directory
SRC_DIR := src

# Directory for generated build files
BUILD_DIR := build

# Temporary ISO filesystem root
ISO_DIR := $(BUILD_DIR)/iso

# Directory where GRUB expects the kernel inside the ISO
BOOT_DIR := $(ISO_DIR)/boot

# Directory where GRUB expects its configuration file
GRUB_DIR := $(BOOT_DIR)/grub


# ------------------------------------------------------------
# Output files
# ------------------------------------------------------------

# Final kernel binary loaded by GRUB
KERNEL := $(BUILD_DIR)/kernel.elf

# Final bootable ISO image
ISO := $(BUILD_DIR)/janOS.iso


# ------------------------------------------------------------
# Object files
# ------------------------------------------------------------

# Object files that will be linked into the kernel
OBJS := \
	$(BUILD_DIR)/boot.o \
	$(BUILD_DIR)/kernel.o


# ------------------------------------------------------------
# Main targets
# ------------------------------------------------------------

# Default target.
all: $(KERNEL)

# Build the bootable ISO image.
iso: $(ISO)

# Run the ISO in QEMU.
run: $(ISO)
	$(QEMU) -boot d -cdrom $(ISO) -m 128M

# Remove all generated files.
clean:
	rm -rf $(BUILD_DIR)

# Show available make commands.
help:
	@echo "janOS build commands:"
	@echo "  make        Build the kernel ELF"
	@echo "  make iso    Build a bootable GRUB ISO"
	@echo "  make run    Run the ISO in QEMU"
	@echo "  make clean  Remove build files"


# ------------------------------------------------------------
# Build rules
# ------------------------------------------------------------

# Create the build directory.
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build boot.o from boot.S.
$(BUILD_DIR)/boot.o: $(SRC_DIR)/boot.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build kernel.o from kernel.c.
$(BUILD_DIR)/kernel.o: $(SRC_DIR)/kernel.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link all object files into the final kernel ELF.
$(KERNEL): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) $(OBJS) -o $@


# ------------------------------------------------------------
# ISO creation
# ------------------------------------------------------------

# Create a GRUB bootable ISO image.
$(ISO): $(KERNEL) grub.cfg
	mkdir -p $(GRUB_DIR)
	cp $(KERNEL) $(BOOT_DIR)/kernel.elf
	cp grub.cfg $(GRUB_DIR)/grub.cfg
	$(GRUB_MKRESCUE) -o $@ $(ISO_DIR)


# ------------------------------------------------------------
# Phony targets
# ------------------------------------------------------------

.PHONY: all iso run clean help
