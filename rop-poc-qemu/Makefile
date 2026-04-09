CC := riscv64-unknown-elf-gcc
SRCS := start.S hello.c
LINKER := link.ld
TARGET := hello

CFLAGS := -nostdlib -nostartfiles -march=rv64imac -mabi=lp64 -mcmodel=medany -T $(LINKER)

all: $(TARGET)

$(TARGET): $(SRCS) $(LINKER)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

.PHONY: qemu
qemu: $(TARGET)
	qemu-system-riscv64 -machine virt -nographic -bios none -kernel $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
