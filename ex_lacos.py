soma = 0

while True:
    num = int(input("Digite um número: "))
    if num == -1:
        break
    soma += num

print(f"A soma dos números digitados é {soma}")
