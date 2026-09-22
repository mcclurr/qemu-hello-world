set confirm off
set remotetimeout 240

# Connect to QEMU's built-in GDB server
target extended-remote :1234

printf "Elf Path received: %s\n", $elf_path

eval "file %s", $elf_path

# Catch OpenSBI handing control to our application
break _start

# Catch hart 2 when OpenSBI HSM starts it
break _secondary_start

# Let OpenSBI initialize and hand off to the application
continue