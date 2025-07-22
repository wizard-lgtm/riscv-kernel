.section .text
.globl _start
.globl kmain
_start:
    la sp, stack_top
    call kmain
1:  j 1b

.section .bss
.align 12
.space 0x4000
stack_top:

