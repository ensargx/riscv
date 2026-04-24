.section .text
.global _start
.global exit

_start:
    /* set stack pointer */
    lui sp, (128*1024)>>12
    /* call main */
    jal ra, main

exit:
    /* signal completion */
    li a0, 0x20000000
    li a1, 123456789
    sw a1, 0(a0)

    /* trap */
    ebreak
