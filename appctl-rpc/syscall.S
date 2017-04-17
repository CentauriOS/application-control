.globl chmod
.globl close
.globl connect
.globl getgid
.globl getuid
.globl lseek
.globl open
.globl read
.globl rename
.globl sendmsg
.globl socket
.globl stat
.globl unlink
.globl write

chmod:
    mov $90, %rax
    syscall
    neg %rax
    mov %rax, _errno
    neg %rax
    ret

close:
    mov $3, %rax
    syscall
    neg %rax
    mov %rax, _errno
    neg %rax
    ret

connect:
    mov $42, %rax
    syscall
    neg %rax
    mov %rax, _errno
    neg %rax
    ret

getgid:
    mov $104, %rax
    syscall
    neg %rax
    mov %rax, _errno
    neg %rax
    ret

getuid:
    mov $102, %rax
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

sendmsg:
    mov $46, %rax
    syscall
    neg %rax
    mov %rax, _errno
    neg %rax
    ret

socket:
    mov $41, %rax
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
