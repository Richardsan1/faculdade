.data
initphr: .asciiz "Digite a nova senha: "
testphr: .asciiz "Digite a senha: "
right: .asciiz "Correto\nFim do programa\n"
wrong: .asciiz "Incorreto\n"
buffer: .asciiz "          "
bufferread: .asciiz "          "
.text

# recebendo a senha inicial
la $a0, initphr
li $v0, 4
syscall

la $a0, buffer
li $a1, 11
li $v0, 8
syscall

loop:
    # recebendo uma string
    li $v0, 4
    la $a0, testphr
    syscall

    la $a0, bufferread
    li $a1, 11
    li $v0, 8
    syscall

    # carrega os enderecos das strings
    la $t0, buffer
    la $t1, bufferread

# compara as strings
compare_loop:
    lb $t2, 0($t0)  # Caractere atual da primeira string
    lb $t3, 0($t1)  # Caractere atual da segunda string

    beq $t2, $zero, continue  # Se fim da string, continue
    bne $t2, $t3, error       # Se caracteres diferentes, erro

    addi $t0, $t0, 1  # Proximo caractere da primeira string
    addi $t1, $t1, 1  # Proximo caractere da segunda string
    j compare_loop

error:
    # Imprime a mensagem de erro
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