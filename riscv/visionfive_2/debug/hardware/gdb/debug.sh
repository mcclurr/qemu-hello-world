#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ELF_DIR="$(cd "$SCRIPT_DIR/../../src/double_hart" && pwd)"

# echo "SCRIPT_DIR: $SCRIPT_DIR"
# echo "ELF_DIR:    $ELF_DIR"
# echo "ELF:        $ELF_DIR/hello.elf"

riscv-none-elf-gdb \
    -tui \
    -ex "set substitute-path /workspace/riscv/visionfive_2/src/double_hart $ELF_DIR" \
    "$ELF_DIR/hello.elf"
    # -x "$SCRIPT_DIR/debug.gdb"