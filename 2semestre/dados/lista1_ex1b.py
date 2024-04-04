import matplotlib.pyplot as plt
import random

set = [random.randint(1, 100) for _ in range(15)]
ordered_set = sorted(set)
m = sum(ordered_set)/len(ordered_set)
s2 = sum([(x - m)**2 for x in ordered_set]) / len(ordered_set)
s = s2**0.5

print(f"Set: {ordered_set}\n")
print(f"Media: {m:.2f}")
print(f"Mediana: {ordered_set[7]}")
print(f"Variancia: {s2:.2f}")
print(f"Desvio Padrao: {s:.2f}")
print(f"coeficiente de variacao: {(s/m)*100:.2f}")
print(f"Q1: {ordered_set[3]}")
print(f"Q3: {ordered_set[11]}")

plt.hist(ordered_set, bins=10)
plt.title('Histogram')
plt.xlabel('Values')
plt.ylabel('Frequency')
plt.show()

plt.boxplot(ordered_set)
plt.title('Box Plot')
plt.ylabel('Values')
plt.show()