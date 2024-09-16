.data
prompt: .asciiz "Escolha um numero: "
even: .asciiz "Eh par\n"
odd: .asciiz "Eh impar\n"

.text
# recebe um numero
la $a0, prompt
li $v0, 4
syscall

li $v0, 5
syscall

# faz a divisao por 2
li $t0, 2
div $v0, $t0

# pega o resto
mfhi $t1

# se o resto for igual a 0 vai para a label equal
beqz $t1, equal
# caso o contrario, printa "Eh impar"
la $a0, odd
li $v0, 4
syscall
# acaba o programa
j end

# printa "eh par"
equal:
    la $a0, even
    li $v0, 4
    syscall

end:
