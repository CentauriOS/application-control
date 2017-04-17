.globl close
.globl chmod
.globl lseek
.globl open
.globl read
.globl rename
.globl stat
.globl unlink
.globl write

close:
    mov $3, %rax
    syscall
    neg %rax
    mov %rax, _errno
    neg %rax
    ret

chmod:
    mov $90, %rax
    syscall
    neg %rax
    mov %rax, _errno
    neg %rax
    ret

lseek:
    mov $8, %rax
    syscall
    neg %rax
    mov %rax, _errno
    neg %rax
    ret

open:
    mov $2, %rax
    syscall
    neg %rax
    mov %rax, _errno
    neg %rax
    ret

read:
    xor %rax, %rax
    syscall
    neg %rax
    mov %rax, _errno
    neg %rax
    ret

rename:
    mov $82, %rax
    syscall
    neg %rax
    mov %rax, _errno
    neg %rax
    ret

stat:
    mov $4, %rax
    syscall
    neg %rax
    mov %rax, _errno
    neg %rax
    ret

unlink:
    mov $87, %rax
    syscall
    neg %rax
    mov %rax, _errno
    neg %rax
    ret

write:
    mov $1, %rax
    syscall
    neg %rax
    mov %rax, _errno
    neg %rax
    ret
