.data
fibonacci_a: .word 0
fibonacci_b: .word 0
fibonacci_c: .word 0
main_num: .word 0
main_result: .word 0
.text
li $t0, 0
la $t1, fibonacci_a
sw $t0, 0($t1)
li $t0, 1
la $t1, fibonacci_b
sw $t0, 0($t1)
li $t0, 0
la $t1, fibonacci_c
sw $t0, 0($t1)
L0:
la $t1, fibonacci_n
lw $t0, 0($t1)
li $t1, 1
slt $t2, $t1, $t0
beq $t2, $zero, L1
la $t1, fibonacci_a
lw $t0, 0($t1)
la $t2, fibonacci_b
lw $t1, 0($t2)
add $t2, $t0, $t1
la $t0, fibonacci_c
sw $t2, 0($t0)
la $t1, fibonacci_b
lw $t0, 0($t1)
la $t1, fibonacci_a
sw $t0, 0($t1)
la $t1, fibonacci_c
lw $t0, 0($t1)
la $t1, fibonacci_b
sw $t0, 0($t1)
la $t1, fibonacci_n
lw $t0, 0($t1)
li $t1, 1
sub $t2, $t0, $t1
la $t0, fibonacci_n
sw $t2, 0($t0)
j L0
L1:
la $t1, fibonacci_b
lw $t0, 0($t1)
la $t1, fibonacci_result
sw $t0, 0($t1)
jr $ra
li $t0, 10
la $t1, main_num
sw $t0, 0($t1)
li $t0, 0
la $t1, main_result
sw $t0, 0($t1)
la $t1, main_num
lw $t0, 0($t1)
move $a0, $t0
la $t1, main_result
lw $t0, 0($t1)
move $a1, $t0
jal fibonacci
move $t0, $v0
la $t1, main_result
lw $t0, 0($t1)
li $v0, 1
move $a0, $t0
syscall
li $v0, 11
li $a0, 10
syscall
jr $ra
