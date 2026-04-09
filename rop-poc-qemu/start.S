.section .text
.global _start

_start:
    la sp, _stack_top   # stack pointer ayarla

    call main           # main'i çağır

1:  j 1b                # sonsuz loop

.section .bss
.space 4096            # stack
_stack_top:
