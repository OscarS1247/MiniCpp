.data
main_a: .word 0
main_b: .word 0
str_0: .byte 34, 72, 111, 108, 97, 34, 0
str_1: .byte 34, 72, 111, 108, 97, 34, 0
str_2: .byte 34, 65, 100, 105, 111, 115, 34, 0
str_3: .byte 34, 65, 100, 105, 111, 115, 34, 0
str_4: .byte 34, 70, 105, 110, 34, 0
str_5: .byte 34, 70, 105, 110, 34, 0
.text
main:
li $t0, 4
la $t1, main_a
sw $t0, 0($t1)
li $t0, 5
la $t1, main_b
sw $t0, 0($t1)
la $t1, main_a
lw $t0, 0($t1)
la $t2, main_b
lw $t1, 0($t2)
slt $t2, $t0, $t1
xori $t2, $t2, 1
la $t1, main_b
lw $t0, 0($t1)
la $t2, main_a
lw $t1, 0($t2)
slt $t2, $t1, $t0
xori $t2, $t2, 1
or $t0, $t2, $t2
beq $t0, $zero, L0
li $v0, 4
la $a0, str_1
syscall
li $v0, 11
li $a0, 10
syscall
j L1
L0:
li $v0, 4
la $a0, str_3
syscall
li $v0, 11
li $a0, 10
syscall
L1:
L2:
la $t1, main_b
lw $t0, 0($t1)
la $t2, main_a
lw $t1, 0($t2)
slt $t2, $t1, $t0
beq $t2, $zero, L3
la $t1, main_a
lw $t0, 0($t1)
li $t1, 1
add $t2, $t0, $t1
la $t0, main_a
sw $t2, 0($t0)
la $t1, main_a
lw $t0, 0($t1)
li $v0, 1
move $a0, $t0
syscall
li $v0, 11
li $a0, 10
syscall
j L2
L3:
li $v0, 4
la $a0, str_5
syscall
li $v0, 11
li $a0, 10
syscall
