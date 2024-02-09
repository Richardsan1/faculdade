valores = [2,1,5,6,12,13,0,3]

while True:
    aux = None
    for cont in range(0, len(valores)-1):
        if valores[cont] > valores[cont+1]:
            aux = valores[cont+1]
            valores[cont+1] = valores[cont]
            valores[cont] = aux
    if aux == None:
        break

print(valores)
