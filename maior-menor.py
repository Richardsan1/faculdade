N = int(input())
maior = 0
menor = 0

if not(N > 0):
    print("Tamanho inválido!")
else:
    i = 0
    while i < N:
        num = float(input())
        if i == 0:
            maior = num
            menor = num
        else:
            if num > maior:
                maior = num
            if num < menor:
                menor = num
        i += 1
    print(menor)
    print(maior)
