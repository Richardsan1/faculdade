empregados = int(input())

cont = 0
salarios = []
soma = 0

for i in range(empregados):
    salario = float(input())
    if salario >= 3000:
        salario = salario * 1.08
    elif salario >= 2000:
        salario = salario * 1.10
        cont+=1
    else:
        salario = salario * 1.12
    salarios.append(salario)

for i in range(empregados):
    print(f"{salarios[i]:.2f}")
    soma += salarios[i]
print(cont)
print(f"{soma/empregados:.2f}")
