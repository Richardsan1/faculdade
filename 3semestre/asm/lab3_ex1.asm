.data
list_size: .word 0  # Initialize the size of the list to 0
strGetData: .asciiz "digite a quantidade de numeros: "
strGetNum: .asciiz "digite o numero "
strDoisPontos: .asciiz ": "
strSorted: .asciiz "Lista ordenada: "
strVirgula: .asciiz ", "

.text


# t0 = tamanho da lista
# t1 = endereco do inicio da lista
# t2 = endereco do fim da lista
# t3 = endereco do elemento atual

main:
    jal getData
    # jal bubblesort
    jal printList

    li $v0, 17
    syscall


# $t4 = quantos elementos ja foram inseridos só para o print
getData:
    # Print the message to get the number of elements
    li $v0, 4
    la $a0, strGetData
    syscall

    # Read the number of elements
    li $v0, 5
    syscall

    # Store the number of elements in $t0
    sw $v0, list_size

    # Allocate space for the list
    li $v0, 9
    sll $a0, $t0, 2  # $a0 = $t0 * 4
    syscall

    # Store the address of the list in $t1
    move $t1, $v0

    # Store the address of the end of the list in $t2
    add $t2, $t1, $a0

    # carrega o primeiro endereco
    move $t3, $t1
    li $t4, 1
    
    loop:
        li $v0, 4
        la $a0, strGetNum
        syscall

        li $v0, 1
        move $a0, $t4
        syscall
        addi $t4, $t4, 1

        li $v0, 4
        la $a0, strDoisPontos
        syscall

        li $v0, 5
        syscall

        sw $v0, 0($t3)
        addi $t3, $t3, 4

        bne $t3, $t2, loop
    jr $ra

bubbleSort:
    # $s0 = i
    # $s1 = j
    # $s2 = condicao
    # $s3 = swapped
    la $t3, $t1
    li $s0, 0
    loop2:
        li $s3, 0
        li $s1, 0
        loop3:

        add $s2, $s0, 1
        sub $s2, $t0, $s2
        blt $s1, $s2, loop3

    sub $s2, $t0 , 1
    blt $s0, $s2, loop2

# void bubble(int arr[], int n){
#     int swapped;
#     for (int i = 0; i < n - 1; i++) {
#         swapped = 0;
#         for (int j = 0; j < n - i - 1; j++) {
#             if (arr[j] > arr[j + 1]) {
#                 swap(&arr[j], &arr[j + 1]);
#                 swapped = 1;
#             }
#         }

#         // If no two elements were swapped by inner loop,
#         // then break
#         if (swapped == 0){
#             break;
#         }
#     }
# }
printList:
    # Print the sorted list message
    li $v0, 4
    la $a0, strSorted
    syscall

    # Loop through the list and print each element
    print_loop:
        beq $t0, $zero, end_print

        # Load the current element
        lw $a0, 0($t1)

        # Print the element
        li $v0, 1
        syscall

        # Print a space
        li $v0, 4
        la $a0, strVirgula
        syscall

        # Move to the next element
        addi $t1, $t1, 4
        subi $t0, $t0, 1
        j print_loop

    end_print:
    jr $ra