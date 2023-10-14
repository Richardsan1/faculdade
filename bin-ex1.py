#Função de criação das 8 cartas no formato decrescente.
def createCard():
    cards_ = []
    for i in range(7, -1, -1):
        cards_.append(2**i)

    return cards_

#Função para conversão de um número binário (string) em decimal.
def binToDec(binary, cards_):
    dec = 0
    for index, num in enumerate(cards_):
        if binary[index] == "1":
            dec += int(num)

    return dec

#Função para conversão de um número decimal (string) para binário  
def decToBin(decimal, cards_):
    binary = ""
    decimal = int(decimal)
    for num in cards_:
        if decimal >= num:
            binary += "1"
            decimal -= num
        else:
            binary += "0"

    return binary

#Inicialização das variáveis.
cards = createCard()
valorBin = "10000011"
valorDec = "25"

#Alguns testes iniciais para você verificar se o código está correto.
'''
print(cards) 
# deve imprimir [128, 64, 32, 16, 8, 4, 2, 1]

print(valorBin, "em decimal =", BinToDec(valorBin,cards)) 
# deve imprimir 10000011 em decimal = 131

print(valorDec, "em binário =", DecToBin(valorDec, cards)) 
# deve imprimir 25 em binário = 00011001
'''
print(cards)                                              
print(valorBin, "em decimal =", binToDec(valorBin,cards))
print(valorDec, "em binário =", decToBin(valorDec, cards))