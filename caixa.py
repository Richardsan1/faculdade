# Reynaldo Panella - 42306868
# Richard Sanches - 32385374
# Santiago Guevara - 42333067

from os import system, name
import random as r
import getpass as gp
import re

clear = lambda: system('cls' if name == 'nt' else 'clear')  # Limpa a tela

HEADER = '\033[95m' # Cores
BLUE = '\033[94m'
RED = '\u001b[31m'
LIGHT_RED = "\033[1;31m"
ENDC = '\033[0m' # Desativa as cores


# user = {
#     id: 0
#     nome: 1
#     senha: 2
#     telefone: 3
#     email: 4
#     saldo: 5
#     credito: 6
#     credito_gasto: 7
# }
user = [0, "name", "pass", "tel", "email", 0, 0, 0]# Molde do usuário

statement = []  # Extrato bancário

def getAccount(): # verifica se o número da conta está correto
    while True:
        accountId = int(input("INFORME O NÚMERO DA CONTA: "))
        if accountId != user[0]:
            clear()
            print(RED, "ESSA CONTA NÃO EXISTE!", ENDC, sep="")
        else:
            return True

def getPassword(): # verifica se a senha está correta
    err = 0
    
    while True:
        accountPass = gp.getpass("INFORME A SENHA: ")
        if accountPass != user[2]:
            clear()
            print(RED, "SENHA INCORRETA!", ENDC, sep="")
            err += 1
            if err == 3:
                return False
        else:
            return True

def accountRegister(): # cria a conta do usuário
    print(HEADER, "MACK BANK – CADASTRO DE CONTA", ENDC, sep="")
    
    # Cadastra os dados do usuário
    accountNum = r.randint(1000, 9999) # gera um número aleatório de conta
    print(f"NÚMERO DA CONTA: {accountNum}")
    user[0] = accountNum

    while True: # verifica se o nome do usuário é válido
        user[1] = input("NOME DO CLIENTE: ").upper().strip()
        if user[1] != "":
            break
        print(RED, "NOME NÃO PODE SER NULO!", ENDC, sep="")
    while True: # verifica se o telefone do usuário é válido
        user[3] = input("TELEFONE.......: ").strip()
        if user[3] != "":
            break
        print(RED, "TELEFONE NÃO PODE SER NULO!", ENDC, sep="")
    while True: # verifica se o e-mail do usuário é válido
        user[4] = input("E-MAIL.........: ")
        if user[4] != "" and re.match(r"[^@]+@[^@]+\.[^@]+", user[4]):
            break
        else:
            print(RED, "E-MAIL INVÁLIDO!", ENDC, sep='')
    while True: # verifica se o saldo inicial é válido
        user[5] = float(input("SALDO INICIAL...: R$"))
        if user[5] >= 1000.0:
            break
        else:
            print(RED, "SALDO INVÁLIDO! DIGITE UM VALOR MAIOR OU IGUAL A R$1000.00", ENDC, sep="")
    
    while True: # verifica se o saldo inicial é válido
        user[6] = float(input("LIMITE DE CRÉDITO: R$"))
        if user[6] > 0:
            break
        else:
            print(RED, "VALOR DE CRÉDITO INVÁLIDO! DIGITE UM VALOR MAIOR QUE ZERO!", ENDC, sep="")

    while True: # verifica se a senha é igual a senha de confirmação
        user[2] = gp.getpass("SENHA..........: ")
        if len(user[2]) == 6 :
            password_ = gp.getpass("REPITA A SENHA...: ")
            if password_ == user[2]:
                break
            print(RED, "AS SENHAS NÃO COINCIDEM!", ENDC, sep="")
        else:
            print(RED, "A SENHA PRECISA TER SEIS CARACTERES!", ENDC, sep="")
    
    input(f"{BLUE}CADASTRO REALIZADO! PRESSIONE UMA TECLA PARA VOLTAR AO MENU...{ENDC}")
    clear()

def deposit(): # deposita dinheiro na conta
    print(HEADER, "MACK BANK – DEPÓSITO", ENDC, sep="")
    
    getAccount()
    print(f"NOME DO CLIENTE: {user[1]}")

    while True:
        depositValue = float(input("VALOR DO DEPÓSITO: R$"))
        if depositValue > 0: # verifica se o valor do depósito é válido
            user[5] += depositValue # adiciona o depósito ao saldo da conta
            statement.append(f"DEPÓSITO: R${depositValue:.2f}") # adiciona o depósito ao extrato bancário
            break
        else:
            clear()
            print(RED, "VALOR INVÁLIDO!", ENDC, sep="")

    input(f"{BLUE}DEPÓSITO REALIZADO COM SUCESSO! PRESSIONE UMA TECLA PARA VOLTAR AO MENU...{ENDC}")
    clear()

def withdraw(): # saca dinheiro da conta
    print(HEADER, "MACK BANK – SAQUE", ENDC, sep="")
    
    getAccount()
    
    print(f"NOME DO CLIENTE: {user[1]}")
    
    password = getPassword()

    while password:
        withdrawValue = float(input("VALOR DO SAQUE: R$"))
        
        if withdrawValue > 0: # permite o saque se ele for válido
            if user[5] >= withdrawValue: # permite o saque caso o usuário tenha saldo suficiente
                user[5] -= withdrawValue
                statement.append(f"SAQUE: - R${withdrawValue:.2f}")
                print("SAQUE REALIZADO COM SUCESSO!")
                input(f"{BLUE}PRESSIONE UMA TECLA PARA VOLTAR AO MENU...{ENDC}")
                clear()
                break
            elif user[5] + user[6] - user[7] >= withdrawValue: # permite o saque caso o usuário tenha saldo suficiente no crédito, retirando o possivel do saldo e depois descontando do limitem
                print(LIGHT_RED, "VOCÊ ESTÁ USANDO O SEU LIMITE DE CRÉDITO!", ENDC, sep="")

                if user[5] > 0: # verifica se o usuário possui saldo na conta
                    withdrawValue -= user[5]
                    statement.append(f"SAQUE: - R${user[5]:.2f}")
                    user[5] = 0

                user[7] += withdrawValue
                statement.append(f"CRÉDITO: - R${withdrawValue:.2f}")
                print("SAQUE REALIZADO COM SUCESSO!")
                input(f"{BLUE}PRESSIONE UMA TECLA PARA VOLTAR AO MENU...{ENDC}")
                clear()
                break

            else: # não permite o saque caso o usuário não tenha saldo suficiente nem no crédito
                clear()
                print(RED, "VOCÊ NÃO POSSUI SALDO SUFICIENTE!", ENDC, sep="")
                if input("DESEJA TENTAR NOVAMENTE (S/N)?") in "Nn":
                    clear()
                    break
        else:
            clear()
            print(RED, "VALOR INVÁLIDO!", ENDC, sep="")
    return password # retorna True se o usuário errou a senha 3 vezes

def balance(): # mostra o saldo da conta
    print(HEADER, "MACK BANK – CONSULTA SALDO", ENDC, sep="")

    getAccount()

    print(f"NOME DO CLIENTE: {user[1]}")
    password = getPassword()
    if password:
        print(f"SALDO EM CONTA: R${user[5]:.2f}")
        print(f"LIMITE DE CRÉDITO: R${user[6]:.2f}")
        input(f"{BLUE}PRESSIONE UMA TECLA PARA VOLTAR AO MENU...{ENDC}")
        clear()
    return password # retorna False se o usuário errou a senha 3 vezes

def bankStatement(): # mostra o extrato bancário
    print(HEADER, "MACK BANK – EXTRATO DA CONTA", ENDC, sep="")

    getAccount()
    print(f"NOME DO CLIENTE: {user[1]}")
    password = getPassword()

    if password:
        print(f"LIMITE DE CRÉDITO: {user[6]}")
        print(f"SALDO EM CONTA: {user[5]}")
        print("ÚLTIMAS OPERAÇÕES:")
        if statement == []: # verifica se houver operações
            print(LIGHT_RED, "NÃO HÁ OPERAÇÕES RECENTES!", ENDC, sep="")
        else:
            for state in statement:
                print(state)
        input(f"{BLUE}PRESSIONE UMA TECLA PARA VOLTAR AO MENU...{ENDC}")
        clear()

    return password # retorna False se o usuário errou a senha 3 vezes
# função extra
def credit(): # permite o pagamento de crédito consumido
    print(HEADER, "MACK BANK – PAGAMENTO DE CRÉDITO", ENDC, sep="")

    getAccount()
    print(f"NOME DO CLIENTE: {user[1]}")
    password = getPassword()

    if password: # verifica se a senha está correta
        print(f"SALDO EM CONTA: {user[5]}")
        print(f"LIMITE DE CRÉDITO: {user[6]}")
        print(f"CRÉDITO GASTO: {user[7]}")
        print(f"CRÉDITO DISPONÍVEL: {user[6] - user[7]}")
        choice = input("DESEJA PAGAR SEU CRÉDITO? (S/N): ") # verifica se o usuário deseja pagar o crédito
        if choice in "Ss" and user[5] > 0: # verifica se o usuário possui saldo suficiente para pagar o crédito
            val = float(input("QUANTO DESEJA PAGAR: R$ "))
            if val <= user[5] and val > 0: # verifica se o usuário possui saldo para pagar o crédito
                if val >= user[7]: # se o usuário digitar um valor > que a divida, o valor da divida é pago e o restante é desconsiderado
                    user[5] -= user[7]
                    statement.append(f"PAGAMENTO DE CRÉDITO: - R${user[7]:.2f}")
                elif val < user[7]:
                    user[5] -= val
                    user[7] -= val
                    statement.append(f"PAGAMENTO DE CRÉDITO: - R${val:.2f}")

                print("PAGAMENTO REALIZADO COM SUCESSO! SEU CRÉDITO FOI LIBERADO!")
            else:
                print(RED, "VOCÊ NÃO POSSUI SALDO SUFICIENTE PARA EFETUAR O PAGAMENTO!", ENDC, sep="")
        elif choice in "Nn":
            print("PAGAMENTO CANCELADO!")
        else:
            print(RED, "PAGAMENTO CANCELADO! VOCÊ NÃO POSSUI SALDO PARA EFETUAR O PAGAMENTO!", ENDC, sep="")
        input(f"{BLUE}PRESSIONE UMA TECLA PARA VOLTAR AO MENU...{ENDC}")
        clear()
    return password

blocked = False # bloqueia o acesso ao menu caso o usuário erre a senha 3 vezes
clear()
while True: # programa principal

    print(HEADER, "BEM-VINDO AO CAIXA ELETRÔNICO", ENDC, end="\n\n", sep="")
    print("(1) CADASTRAR CONTA CORRENTE")
    print("(2) DEPOSITAR")
    print("(3) SACAR")
    print("(4) CONSULTAR SALDO")
    print("(5) CONSULTAR EXTRATO")
    print("(6) PAGAR CRÉDITO") # nova funcionalidade
    print("(7) FINALIZAR")

    option = input("Digite sua opção: ")
    clear()

    if option == "7":  # Sair
        clear()
        print(HEADER, "MACK BANK – SOBRE", ENDC, sep="")
        print("ESTE PROGRAMA FOI DESENVOLVIDO POR:")
        print("REYNALDO PANELLA")
        print("RICHARD SANCHES")
        print("SANTIAGO GUEVARA")
        break
    elif user[0] == 0: # verifica se o usuário ja possui conta
        if option == "1": # verifica se ele escolheu uma opção possível
            accountRegister()
        else:
            print(RED, "CRIE UMA CONTA ANTES DE TENTAR ACESSAR QUALQUER MENU!", ENDC, sep="")
    else:
        if option == "1":
            print(RED, "CONTA JÁ REGISTRADA", ENDC, sep="")
        elif option == "2":  # Depositar
            deposit()
        elif blocked: # verifica se a conta foi bloqueada
            clear()
            print(RED, "CONTA BLOQUEADA!", ENDC, sep="")
        elif option == "3":  # Sacar
            blocked = not withdraw()
        elif option == "4":  # Saldo
            blocked = not balance()
        elif option == "5":  # Extrato
            blocked = not bankStatement()
        elif option == "6": # crédito
            blocked = not credit()
        else:
            print(RED, "OPÇÃO INVÁLIDA!", ENDC, sep="")
