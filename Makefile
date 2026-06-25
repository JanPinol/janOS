# ============================================================
# janOS Makefile
# Builds a 32-bit x86 kernel and boots it with GRUB/Multiboot
#
# Sources are discovered recursively, so adding a new .c under
# arch/, drivers/, kernel/ or lib/ requires no Makefile changes.
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

ARCH_DIR = arch/x86
BOOT_DIR = $(ARCH_DIR)/boot

BUILD_DIR = build
ISO_ROOT = $(BUILD_DIR)/iso
ISO_BOOT_DIR = $(ISO_ROOT)/boot
ISO_GRUB_DIR = $(ISO_BOOT_DIR)/grub

INCLUDE_DIRS = \
    $(ARCH_DIR)/include \
    drivers/include \
    kernel/include \
    lib/include

# ------------------------------------------------------------
# Output files
# ------------------------------------------------------------

KERNEL_ELF = $(BUILD_DIR)/kernel.elf
ISO_IMAGE = $(BUILD_DIR)/janOS.iso

# ------------------------------------------------------------
# Flags
# ------------------------------------------------------------

CFLAGS = -m32 \
    -std=gnu11 \
    -Wall -Wextra \
    -O2 -g \
    -ffreestanding \
    -nostdlib \
    -nostartfiles \
    -fno-pie \
    -fno-stack-protector \
    -MMD -MP \
    $(addprefix -I,$(INCLUDE_DIRS))

LDFLAGS = -m elf_i386 \
    -n \
    -T $(BOOT_DIR)/linker.ld

# ------------------------------------------------------------
# Source and object discovery
#
# Every object mirrors its source path under $(BUILD_DIR), e.g.
# arch/x86/gdt.c -> build/arch/x86/gdt.o
# ------------------------------------------------------------

C_SRCS = $(shell find $(ARCH_DIR) drivers kernel lib -name '*.c')
ASM_SRCS = $(shell find $(BOOT_DIR) -name '*.S')

OBJS = \
    $(C_SRCS:%.c=$(BUILD_DIR)/%.o) \
    $(ASM_SRCS:%.S=$(BUILD_DIR)/%.o)

DEPS = $(OBJS:.o=.d)

# ------------------------------------------------------------
# Main targets
# ------------------------------------------------------------

all: $(KERNEL_ELF)

iso: $(ISO_IMAGE)

run: $(ISO_IMAGE)
	$(QEMU) -boot d -cdrom $(ISO_IMAGE) -m 128M -k es

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo "janOS build commands:"
	@echo "  make        Build the kernel ELF"
	@echo "  make iso    Build a bootable GRUB ISO"
	@echo "  make run    Run the ISO in QEMU"
	@echo "  make clean  Remove generated files"

# ------------------------------------------------------------
# Compilation rules
# ------------------------------------------------------------

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	@mkdir -p $(dir $@)
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
# Auto-generated header dependencies
# ------------------------------------------------------------

-include $(DEPS)

# ------------------------------------------------------------
# Phony targets
# ------------------------------------------------------------

.PHONY: all iso run clean help
