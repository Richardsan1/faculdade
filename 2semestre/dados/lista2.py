import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def calculate_and_plot_linear_regression(x, y):
    coefficients = np.polyfit(x, y, 1)
    linear_regression = np.poly1d(coefficients)
    plt.scatter(x, y)

    plt.plot(x, linear_regression(x), color='red')
    plt.show()

    return linear_regression

df = pd.read_csv('death.csv')
set = df['Average Deaths per Year']
ordered_set = sorted(set)
ordered_set = [int(i) for i in ordered_set if str(i).isdigit()]

x = np.array(range(len(ordered_set)))
y = np.array(ordered_set)

print("coeficientes: ", calculate_and_plot_linear_regression(x, y))
