import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

df = pd.read_csv('death.csv')
set = df['Average Deaths per Year']

ordered_set = sorted(set)
ordered_set = [int(i) for i in ordered_set if str(i).isdigit()]
m = sum(ordered_set)/len(ordered_set)
s2 = sum([(x - m)**2 for x in ordered_set]) / len(ordered_set)
s = s2**0.5

print(f"Media: {m:.2f}")
print(f"Mediana: {ordered_set[len(ordered_set)//2]}")
print(f"Variancia: {s2:.2f}")
print(f"Desvio Padrao: {s:.2f}")
print(f"coeficiente de variacao: {(s/m)*100:.2f}")
print(f"Q1: {ordered_set[len(ordered_set)//4]}")
print(f"Q3: {ordered_set[(len(ordered_set)*3)//4]}")

plt.hist(ordered_set, bins=10)
plt.title('Histogram')
plt.xlabel('quantidade de mortes')
plt.ylabel('Frequencia')
plt.show()

plt.boxplot(ordered_set)
plt.title('Box Plot')
plt.ylabel('Values')
plt.show()