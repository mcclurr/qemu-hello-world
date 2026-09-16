set confirm off
set remotetimeout 240

target extended-remote 172.20.240.1:3334

# Load hello.elf into RAM
load

# Work with hart 1
thread 1

# Start hart 1 at our application's entry point
set $pc = _start

# Break when we enter main
break main

continue