main:
    # Recebendo a senha
    li $v0, 4
    la $a0, phr
    syscall

    li $v0, 5
    syscall
    move $t1, $v0  # Armazena a senha digitada em $t1

    # Carrega a senha correta
    lw $t0, password

    # Comparar bit a bit
    li $t3, 32  # Número de bits em uma word
    li $t4, 0   # Índice do bit

compare_bits:
    beq $t4, $t3, success  # Se todos os bits foram comparados, sucesso

    # Extrair o bit atual das duas senhas
    srl $t5, $t0, $t4  # Desloca a senha correta para a direita
    srl $t6, $t1, $t4  # Desloca a senha digitada para a direita
    andi $t5, $t5, 1   # Isola o bit menos significativo
    andi $t6, $t6, 1   # Isola o bit menos significativo

    # Comparar os bits
    bne $t5, $t6, error  # Se os bits são diferentes, erro

    addi $t4, $t4, 1  # Incrementa o índice do bit
    j compare_bits

error:
    # Se estiver errado, imprime errado
    la $a0, wrong
    li $v0, 4
    syscall
    j end

success:
    # Se estiver correto, imprime correto
    la $a0, correct
    li $v0, 4
    syscall

end:
    # Finaliza o programa
    li $v0, 10
    syscall

.data
phr: .asciiz "Digite a senha: "
wrong: .asciiz "Senha incorreta\n"
correct: .asciiz "Senha correta\n"
password: .word 0x12345678  # Exemplo de senha correta