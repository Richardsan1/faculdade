val = [2,1,5,6,12,13,0,3]
def bubbleSort(valores):
    while True:
        aux = None
        for cont in range(0, len(valores)-1):
            if valores[cont] > valores[cont+1]:
                aux = valores[cont+1]
                valores[cont+1] = valores[cont]
                valores[cont] = aux
        if aux == None:
            break
    return valores

cadaSort = []

print("digite 0 para sair")
while True:
    valores = []
    nums = int(input("Digite a quantidade de numeros: "))
    
    if nums == 0:
        break
    
    for i in range(0, nums):
        valor = input("digite um valor:").strip()

        if len(valor) != 4:
            continue
        valores.append(valor)
    cadaSort.append(bubbleSort(valores))

print("\n")
for sort in cadaSort:
    for val in sort:
        print(val)
    print()