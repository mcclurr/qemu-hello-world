#!/bin/bash

# Directory containing this script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Project root is two directories above qemu/run.sh
PROJECT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"

# ELF to boot
ELF="$PROJECT_DIR/src/double_hart/hello.elf"

qemu-system-riscv64 \
    -machine virt \
    -smp 4 \
    -m 2G \
    -nographic \
    -kernel "$ELF" \
    -S \
    -gdb tcp::1234