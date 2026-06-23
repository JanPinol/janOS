# Multiboot constants for GRUB
.set MAGIC, 0x1BADB002
.set FLAGS, 0
.set CHECKSUM, -(MAGIC + FLAGS)

# Multiboot header.
# GRUB looks for this header to recognize the file as a bootable kernel.
.section .multiboot,"a" # allocable
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Kernel executable code starts here
.section .text.boot,"ax" # allocable and executable
.global _start
.extern kernel_main

# Kernel entry point.
# GRUB jumps here after loading the kernel.
_start:
    # Set up the stack pointer before calling C code
    mov $stack_top, %esp

    # Jump into the C kernel entry point
    call kernel_main

# If kernel_main ever returns, stop the CPU forever
halt:
    hlt
    jmp halt

# Uninitialized data section.
# We reserve memory here for the kernel stack.
.section .bss
.align 16

stack_bottom:
    # Reserve 16 KiB for the kernel stack
    .skip 16384

stack_top:
