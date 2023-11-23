from os import system, name

def anyToDec(value, base):
    dec = 0
    
    for i in range(len(value)):
        dec += int(value[i]) * (base ** (len(value) - 1 - i))
    
    return dec

def decToAny(value, base):
    num = ""
    
    while value > 0:
        num = str(value % base) + num
        value = value // base
    
    return num

def info():
    print("*" * 30)
    print("Grupo:")
    print("- Nome: Richard Barbosa Sanches")
    print("- TIA: 32385374")
    print("*" * 30)

system("cls" if name == "nt" else "clear")
system("color 02" if name == "nt" else "tput setaf 2")

while True:
    print("""[1] Converter de bin/octal/hex para decimal
[2] Converter de decimal para bin/octal/hex
[3] informações do grupo
[4] Sair
""")
    try:
        op = int(input("Digite a opção desejada: "))
        if op < 1 or op > 4:
            raise ValueError
    except ValueError:
        system("cls" if name == "nt" else "clear")
        print("Opção inválida!\n")
        continue
    
    if op == 1:
        try:
            value = input("Digite o número a ser convertido: ")
            base = int(input("Digite a base do número(2, 8, 16): "))
            if base != 2 and base != 8 and base != 16:
                raise ValueError
        except ValueError:
            system("cls" if name == "nt" else "clear")
            print("Valor inválido!\n")
            continue

        print(f"\n{value} === {anyToDec(value, base)}\n")
        input("Pressione enter para continuar...")
        system("cls" if name == "nt" else "clear")
    
    elif op == 2:
        try:
            value = int(input("Digite o número a ser convertido: "))
            base = int(input("Digite a base do número (2, 8 ou 16): "))
            if base != 2 and base != 8 and base != 16:
                raise ValueError
        except ValueError:
            system("cls" if name == "nt" else "clear")
            print("Valor inválido!\n")
            continue

        print(f"\n{value} === {decToAny(value, base)}\n")
        input("Pressione enter para continuar...")
        system("cls" if name == "nt" else "clear")
    
    elif op == 3:
        info()
        input("Pressione enter para continuar...")
        system("cls" if name == "nt" else "clear")
    
    elif op == 4:
        system("color 07 && cls" if name == "nt" else "clear")
        break
