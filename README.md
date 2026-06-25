# janOS

Tiny educational x86 32-bit operating system.

## Current features
- Multiboot boot through GRUB
- 32-bit x86 kernel (flat GDT, IDT)
- CPU exception handlers (ISRs)
- Hardware interrupts (PIC remap, IRQs) with a driver-registered handler table
- PIT timer (100 Hz) and system uptime
- PS/2 keyboard driver (Spanish layout) with a ring buffer
- VGA text output and a scrolling terminal
- Freestanding libc subset (`string`, `stdlib`, `kprintf`)
- Minimal interactive shell (`help`, `clear`, `uptime`, `echo`)
- QEMU execution

## Project layout
```
arch/x86/      x86-specific code
  boot/        Multiboot entry, GDT/IDT loaders, ISR/IRQ stubs, linker, GRUB cfg
  include/arch/  CPU headers   -> #include <arch/idt.h>
  *.c          GDT, IDT, ISR, IRQ, PIC, port I/O
drivers/       hardware drivers (keyboard, PIT timer, VGA, TTY)
  include/drivers/             -> #include <drivers/keyboard.h>
kernel/        architecture-independent core (entry, shell)
  include/kernel/              -> #include <kernel/shell.h>
lib/           freestanding libc (standard names: #include <stdio.h>)
build/         generated objects, ELF and ISO (git-ignored)
```

## Coding style
Linux kernel conventions with **4-space** indentation. The rules are encoded
in [.clang-format](.clang-format) and [.editorconfig](.editorconfig); run
`clang-format -i <file>` or enable EditorConfig in your editor.

## Requirements
```
sudo apt install build-essential git make grub-pc-bin grub-common xorriso qemu-system-x86
```

## Build
```
make        # build the kernel ELF
make iso    # build a bootable GRUB ISO
make run    # run the ISO in QEMU
make clean  # remove generated files
```
