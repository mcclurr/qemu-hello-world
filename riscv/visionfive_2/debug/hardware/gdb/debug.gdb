set confirm off
set remotetimeout 240

target extended-remote 172.20.240.1:3334

# Load hello.elf into RAM
load

# Catch OpenSBI handing control to our application
break _start

# Catch hart 2 when OpenSBI HSM starts it
break _secondary_start

# Let OpenSBI initialize and hand off to the application
continue