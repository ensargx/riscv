#define UART0 0x10000000

void uart_putc(char c) {
    *(volatile char*)UART0 = c;
}

void uart_puts(char *s) {
    while (*s) {
        uart_putc(*s++);
    }
}

/* example function which is not supposed to be called */
void win() {
    uart_puts("PoC\n");
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
    memcpy_("AAAAAAAABBBBBBBBDDDDDDDD\x6c\x00\x00\x80\x00\x00\x00\x00", target, 32);
}

int main() {
    /* 16 bytes of buffer */
    char arr[16];

    uart_puts("Hello RISC-V (UART)!\n");
    /* arbitary size of input */
    memcpy_vuln(arr);

    return 0;
}
