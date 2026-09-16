#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"

ELF="$PROJECT_DIR/src/double_hart/hello.elf"
GDB_SCRIPT="$SCRIPT_DIR/debug.gdb"

riscv-none-elf-gdb \
    -tui \
    -x "$GDB_SCRIPT" \
    "$ELF"