.globl _start
.globl __stack_chk_fail

_start:
    pop %rdi
    mov %rsp, %rsi
    call main
    movl %eax, %ebx
    movl $1, %eax
    int $0x80

__stack_chk_fail:
    movl $-1, %ebx
    movl $1, %eax
    int $0x80
