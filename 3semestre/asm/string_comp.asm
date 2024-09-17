.data
testphr: .asciiz "Digite a senha: "
right: .asciiz "Correto\nFim do programa\n"
wrong: .asciiz "Incorreto\n"
password: .word 1010502

.text

loop:
    # recebendo a senha
    li $v0, 4
    la $a0, testphr
    syscall

    li $v0, 5
    syscall

    # compara as senhas
    lw $t1, password
    beq $v0, $t1, continue
    
    # se estiver errado, printa errado
    la $a0, wrong
    li $v0, 4
    syscall

    # Volta para o loop
    j loop

continue:
    # Imprime a mensagem do fim do programa
    la $a0, right
    li $v0, 4
    syscall
