import math as m

def exibeMsg():
    print("Programa para conversão de temperatura")
    print(" • Digite F para converter de Fahrenheit para Celsius")
    print(" • Digite C para converter de Celsius para Fahrenheit")

def verificaOpcao():
    opcao = input("Digite a opção desejada: ").upper().strip()
    while opcao != "F" and opcao != "C":
        print("Opção inválida!")
        opcao = input("Digite a opção desejada: ").upper().strip()
    return opcao

def verificaIntervalo():
    inicio = float(input("Digite o valor inicial do intervalo: "))
    fim = float(input("Digite o valor final do intervalo: "))
    while inicio >= fim:
        print("Valor inicial deve ser menor que o valor final!")
        inicio = float(input("Digite o valor inicial do intervalo: "))
        fim = float(input("Digite o valor final do intervalo: "))
    return inicio, fim

def exibeFahrenheitToCelsius(inicio, fim):
    for fahren in range(int(inicio), int(fim)+1):
        celsius = (fahren - 32) / 1.8
        print(f"{celsius:.2f}")
        celsius = m.ceil(round(celsius,1)*10)/10
        print(f"{fahren}°F = {celsius:.1f}°C")

def exibeCelsiusToFahrenheit(inicio, fim):
    for celsius in range(int(inicio), int(fim)+1):
        fahrenheit = celsius *1.8 + 32
        print(f"{fahrenheit:.2f}")
        fahrenheit = m.ceil(round(fahrenheit,1)*10)/10
        print(f"{celsius}°C = {fahrenheit:.1f}°F")


def main():
    exibeMsg()
    opcao = verificaOpcao()
    ini, fim = verificaIntervalo()
    if opcao == "F":
        exibeFahrenheitToCelsius(ini, fim)
    elif opcao == "C":
        exibeCelsiusToFahrenheit(ini, fim)

main()