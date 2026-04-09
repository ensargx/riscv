// hello.c
// David_Harris@hmc.edu 30 November 2024
// SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1

// Hello World program illustrating compiled C code printing via the UART
// The Wally team has modified the Berkeley syscalls.c (in examples/C/common)
// to print via UART rather than the syscall interface.  This is supported
// on both Spike and Wally.  It assumes the PC16550-compatible UART is at
// the default SiFive address of 0x10000000.
// Note that there seem to be some discrepancies between the UART and Spike
// such that using \n\r for new lines works best.

// compile with make
// simulate Wally with: wsim rv64gc --elf hello --sim verilator
// simulate in Spike with: spike hello

#include <stdio.h>

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

