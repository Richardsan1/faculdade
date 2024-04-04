import matplotlib.pyplot as plt
import random

def orderSet(set: list):
    size = len(set)
    for i in range(size):
        for j in range(0, size - i - 1):
            if set[j] > set[j + 1]:
                set[j], set[j + 1] = set[j + 1], set[j]
    return set

def variancia(set: list):
    media = sum(set)/len(set)
    soma = 0
    
    for val in set:
        soma += (val - media)**2

    return soma/(len(set)-1)

set = orderSet(set = [random.randint(1, 100) for _ in range(15)])
# set = [i for i in range(0, 15)]
m = sum(set)/len(set)
s2 =  variancia(set)
s = s2**0.5

print(f"Set: {set}\n")
print(f"Media: {m:.2f}")
print(f"Mediana: {set[7]}")
print(f"Variancia: {s2:.2f}")
print(f"Desvio Padrao: {s:.2f}")
print(f"coeficiente de variacao: {(s/m)*100:.2f}")
print(f"Q1: {set[3]}")
print(f"Q3: {set[11]}")

plt.hist(set, bins=5)
plt.show()
# 

plt.boxplot(set)
plt.show()