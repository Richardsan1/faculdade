import matplotlib.pyplot as plt
import pandas as pd

def soma(data):
    total = 0
    for i in data:
        total += i
    return total

def calculate_mean(data):
    return soma(data) / len(data)

def calculate_median(data):
    n = len(data)
    if n % 2 == 1:
        return sorted(data)[n//2]
    else:
        sorted_data = sorted(data)
        return soma(sorted_data[n//2-1:n//2+1]) / 2

def calculate_variance(data, sample=False):
    mean = calculate_mean(data)
    return soma((x - mean) ** 2 for x in data) / (len(data) - int(sample))

# Rest of your code...

def calculate_std_dev(data, sample=False):
    return calculate_variance(data, sample) ** 0.5

def calculate_cv(data, sample=False):
    return calculate_std_dev(data, sample) / calculate_mean(data) * 100

def calculate_quartiles(data):
    sorted_data = sorted(data)
    n = len(data)
    return sorted_data[n//4], sorted_data[n//2], sorted_data[(n*3)//4]

def plot_histogram(data):
    plt.hist(data, bins=10)
    plt.show()

def plot_boxplot(data):
    plt.boxplot(data)
    plt.show()

df = pd.read_csv('death.csv')
data = df['Average Deaths per Year'].dropna().tolist()
data = [int(i) for i in data if str(i).isdigit()]

print(f"Media: {calculate_mean(data):.2f}")
print(f"Mediana: {calculate_median(data)}")
print(f"Variancia: {calculate_variance(data):.2f}")
print(f"Desvio Padrao: {calculate_std_dev(data):.2f}")
print(f"coeficiente de variacao: {calculate_cv(data):.2f}")
q1, q2, q3 = calculate_quartiles(data)
print(f"Q1: {q1}")
print(f"Q2: {q2}")
print(f"Q3: {q3}")

plot_histogram(data)
plot_boxplot(data)