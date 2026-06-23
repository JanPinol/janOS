# janOS

Tiny educational x86 32-bit operating system.

## Current features
- Multiboot boot through GRUB
- 32-bit x86 kernel
- VGA text output
- Basic terminal abstraction
- QEMU execution

## Requirements
sudo apt install build-essential git make nasm grub-pc-bin grub-common xorriso qemu-system-x86

## Build
make

## Build ISO
make iso

## Run
make run

## Clean
make clean

## Roadmap
- GDT
- IDT
- PIC/PIT
- Keyboard input
- Memory management
- Basic shell
