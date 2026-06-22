# ============================================================
# janOS Makefile
# Builds a 32-bit x86 kernel and boots it with GRUB/Multiboot
# ============================================================


# ------------------------------------------------------------
# Tools
# ------------------------------------------------------------

CC = gcc
LD = ld
QEMU = qemu-system-i386
GRUB_MKRESCUE = grub-mkrescue


# ------------------------------------------------------------
# Project paths
# ------------------------------------------------------------

KERNEL_DIR = kernel

BOOT_DIR = $(KERNEL_DIR)/boot
SRC_DIR = $(KERNEL_DIR)/src
INCLUDE_DIR = $(KERNEL_DIR)/include

BUILD_DIR = build
ISO_ROOT = $(BUILD_DIR)/iso
ISO_BOOT_DIR = $(ISO_ROOT)/boot
ISO_GRUB_DIR = $(ISO_BOOT_DIR)/grub


# ------------------------------------------------------------
# Output files
# ------------------------------------------------------------

KERNEL_ELF = $(BUILD_DIR)/kernel.elf
ISO_IMAGE = $(BUILD_DIR)/janOS.iso


# ------------------------------------------------------------
# Flags
# ------------------------------------------------------------

CFLAGS = -m32 \
         -Wall -Wextra \
         -O2 -g \
         -ffreestanding \
         -nostdlib \
         -nostartfiles \
         -fno-pie \
         -fno-stack-protector \
         -I$(INCLUDE_DIR)

LDFLAGS = -m elf_i386 \
          -T $(BOOT_DIR)/linker.ld


# ------------------------------------------------------------
# Source files and object files
# ------------------------------------------------------------

# Find all C source files inside kernel/src
C_SRCS = $(wildcard $(SRC_DIR)/*.c)

# Convert:
# kernel/src/kernel.c -> build/kernel.o
# kernel/src/vga.c    -> build/vga.o
C_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SRCS))

# Final object list
OBJS = \
	$(BUILD_DIR)/boot.o \
	$(C_OBJS)


# ------------------------------------------------------------
# Main targets
# ------------------------------------------------------------

# Build only the kernel ELF
all: $(KERNEL_ELF)

# Build a bootable ISO image
iso: $(ISO_IMAGE)

# Run the ISO in QEMU
run: $(ISO_IMAGE)
	$(QEMU) -boot d -cdrom $(ISO_IMAGE) -m 128M

# Remove generated files
clean:
	rm -rf $(BUILD_DIR)

# Show available commands
help:
	@echo "janOS build commands:"
	@echo "  make        Build the kernel ELF"
	@echo "  make iso    Build a bootable GRUB ISO"
	@echo "  make run    Run the ISO in QEMU"
	@echo "  make clean  Remove generated files"


# ------------------------------------------------------------
# Build directories
# ------------------------------------------------------------

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


# ------------------------------------------------------------
# Compilation rules
# ------------------------------------------------------------

# Compile boot assembly
$(BUILD_DIR)/boot.o: $(BOOT_DIR)/boot.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile any C file from kernel/src into build/*.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


# ------------------------------------------------------------
# Link kernel
# ------------------------------------------------------------

$(KERNEL_ELF): $(OBJS) $(BOOT_DIR)/linker.ld
	$(LD) $(LDFLAGS) $(OBJS) -o $@


# ------------------------------------------------------------
# Create bootable ISO
# ------------------------------------------------------------

$(ISO_IMAGE): $(KERNEL_ELF) $(BOOT_DIR)/grub.cfg
	mkdir -p $(ISO_GRUB_DIR)
	cp $(KERNEL_ELF) $(ISO_BOOT_DIR)/kernel.elf
	cp $(BOOT_DIR)/grub.cfg $(ISO_GRUB_DIR)/grub.cfg
	$(GRUB_MKRESCUE) -o $@ $(ISO_ROOT)


# ------------------------------------------------------------
# Phony targets
# ------------------------------------------------------------

.PHONY: all iso run clean help
