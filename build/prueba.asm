.data
hello: .byte 'H', 'o', 'l', 'a', ':', 0
.text
    li $v0, 4
    la $a0, hello
    syscall
    li $v0, 10
    syscall