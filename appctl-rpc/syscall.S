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
    ret

chmod:
    mov $90, %rax
    syscall
    ret

lseek:
    mov $8, %rax
    syscall
    ret

open:
    mov $2, %rax
    syscall
    ret

read:
    xor %rax, %rax
    syscall
    ret

rename:
    mov $82, %rax
    syscall
    ret

stat:
    mov $4, %rax
    syscall
    ret

unlink:
    mov $87, %rax
    syscall
    ret

write:
    mov $1, %rax
    syscall
    ret
