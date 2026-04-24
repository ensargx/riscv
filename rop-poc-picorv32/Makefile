RISCV_PREFIX ?= /opt/riscv/bin/riscv64-unknown-elf-
CC = $(RISCV_PREFIX)gcc
OBJCOPY = $(RISCV_PREFIX)objcopy

CFLAGS = -march=rv32i -mabi=ilp32 -Os -ffreestanding -nostdlib -Ilibc
LDFLAGS = -Wl,-Bstatic,-T,sections.lds,--strip-debug

all: hello.hex

hello.elf: start.S hello.c libc/print.c libc/printf.c libc/string.c sections.lds
	$(CC) $(CFLAGS) $(LDFLAGS) -o hello.elf start.S hello.c libc/print.c libc/printf.c libc/string.c

hello.bin: hello.elf
	$(OBJCOPY) -O binary hello.elf hello.bin

hello.hex: hello.bin
	python3 ../firmware/makehex.py hello.bin 32768 > hello.hex

clean:
	rm -f hello.elf hello.bin hello.hex

.PHONY: all clean
