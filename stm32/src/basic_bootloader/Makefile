.PHONY: all bootloader application clean

all: bootloader application

bootloader:
	$(MAKE) -C bootloader

application:
	$(MAKE) -C application

clean:
	$(MAKE) -C bootloader clean
	$(MAKE) -C application clean
