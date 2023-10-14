qtdTeste = int(input())
testes = []

for i in range(qtdTeste):
    testes.append(input().split(" "))

for _, test in enumerate(testes):
    lamp = test[0]
    rounds = int(test[1])
    
    for i in range(rounds):
        actual = ""
        if lamp[0] == "X":
            actual += "O"
            actual += lamp[1:]
        else:
            actual += "X"
            for j in range(1, len(lamp)):
                if lamp[j-1] == "O" and actual[j-1] == "X":
                    if lamp[j] == "X":
                        actual += "O"
                    else:
                        actual += "X"
                else:
                    actual += lamp[j]
        lamp = actual
    print(lamp)
