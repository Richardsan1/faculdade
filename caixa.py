# Lucas deu ideias e fez o molde do codigo
# Richard finalizou a criação de usuários, sistema de cadastro e login e o sistema de saque e depósito
# Cauã fez as funcionalidades de adm, a transferência entre contas e o limite de depósito
# Guilherme fez a funcionalidade empréstimo e testou as entradas de dados

user = {
    "codigo": 0,
    "nome": "",
    "senha": "",
    "dinheiro": 0
}  # Molde do usuário

# array com todos os usuários cadastrados no sistema
users = [{"codigo": 0, "nome": "adm", "senha": "123", "dinheiro": 0}]
MAX_BANK_NOTES = 2000  # Quantidade máxima de notas no caixa
MAX_LOAN = 1000  # Limite de empréstimo
bank_notes = 0  # Quantidade de notas no caixa
activeUser = -1
isLogged = False
isAdm = False

money = {
    "200": 0,
    "100": 0,
    "50": 0,
    "20": 0,
    "10": 0,
    "5": 0,
    "2": 0
}  # Dinheiro guardado no caixa

while True:
    if isLogged == False and isAdm == False:
        print("**Bem vindo ao caixa eletrônico**")
        print("\nDigite 1 para se cadastrar")
        print("Digite 2 para acessar sua conta")
        print("Digite 9 para sair")

        option = input("Digite sua opção: ")

        if option == "1":  # Cadastro
            user["codigo"] = int(len(users))
            user["nome"] = input("Digite seu nome: ")
            user["senha"] = input("Digite sua senha: ")
            users.append(user.copy())
            users[int(len(users) - 1)]["dinheiro"] = 0
            print("\nUsuário cadastrado com sucesso")
            print(f"seu código é {user['codigo']}\n")

            input("Pressione ENTER para continuar...")
            print("\n")

            user.clear()
        elif option == "2":  # Login
            code = input("\nDigite seu codigo: ").lower().strip()
            password = input("Digite sua senha: ")
            cont = 0
            if code == "" and password == "":
                print("\nDigite um código e senha")
            elif code == "adm" and password == "123":
                print("adm")
                isAdm = True
            else:
                while cont < len(users):
                    if users[cont]["codigo"] == int(code) and users[cont]["senha"] == password:
                        isLogged = True
                        activeUser = users[cont]["codigo"]
                        print("\nLogado com sucesso\n")
                        break
                    else:
                        cont += 1
                else:
                    print("\nCódigo ou senha incorretos")
                    input("Pressione ENTER para continuar...")
                    print("\n")
        elif option == "9":  # Sair
            break

    elif isAdm:
        print("\nBem vindo administrador")
        print(f"\nCaixa tem {bank_notes} notas\n")
        print("Digite 1 para realizar a sangria")
        print("Digite 2 para realizar a entrada de cedulas")
        print("Digite 3 para realizar a leitura do caixa")
        print("Digite 8 para sair do modo administrador")
        print("Digite 9 para sair do sistema")

        optionAdm = input("Digite sua opção: ")
        if optionAdm == "1":
            bank_notes = 0
            money = {
                "200": 0,
                "100": 0,
                "50": 0,
                "20": 0,
                "10": 0,
                "5": 0,
                "2": 0
            }
            print("\nSangria realizada com sucesso\n")
        elif optionAdm == "2":
            full = False
            total_deposited = 0
            not_deposited = 0
            tempMoney = {
                "200": 0,
                "100": 0,
                "50": 0,
                "20": 0,
                "10": 0,
                "5": 0,
                "2": 0
            }
            print("\nNotas que deseja depositar:\n")
            tempMoney["200"] = int(input("R$200: ") or 0)
            tempMoney["100"] = int(input("R$100: ") or 0)
            tempMoney["50"] = int(input("R$50: ") or 0)
            tempMoney["20"] = int(input("R$20: ") or 0)
            tempMoney["10"] = int(input("R$10: ") or 0)
            tempMoney["5"] = int(input("R$5: ") or 0)
            tempMoney["2"] = int(input("R$2: ") or 0)
            for key in money:
                if tempMoney[key] != 0:
                    while tempMoney[key] > 0:
                        if bank_notes >= MAX_BANK_NOTES:
                            full = True
                            not_deposited += tempMoney[key] * int(key)
                            tempMoney[key] = 0
                            print("\nCaixa lotado")
                            break
                        if not full:
                            money[key] += int(key)
                            total_deposited += int(key)
                            bank_notes += 1
                            tempMoney[key] -= 1
                else:
                    money[key] += 0
            tempMoney.clear()
            if not full:
                print("\nDepósito realizado com sucesso")
                print(f"\nTotal depositado: R${total_deposited}")
            else:
                print(
                    "\nQuantia inserida não pode ser depositada, quantia não depositada será retornada")
                print(
                    "Para remover notas do caixa, será necessário realizar uma sangria")
                print(f"\nTotal depositado: R${total_deposited}")
                print(f"\nTotal não depositado: R${not_deposited}")
            input("Pressione ENTER para continuar...")
            print("\n")
        elif optionAdm == "3":
            print("\nCaixa:")
            for key in money:
                print(f"{key}: {money[key]}")
            input("Pressione ENTER para continuar...")
            print("\n")
        elif optionAdm == "8":
            isAdm = False
            print("\nSaindo do modo administrador\n")
        elif optionAdm == "9":
            break
    elif isLogged:
        print("Digite 1 para depósito")
        print("Digite 2 para saque")
        print("Digite 3 para ver saldo")
        print("Digite 4 para transferir")
        print("Digite 5 para fazer um empréstimo")
        print("Digite 8 para sair do perfil")
        print("Digite 9 para sair\n")

        optionLogged = input("Digite sua opção: ")

        if optionLogged == "1":  # Depósito
            full = False
            total_deposited = 0
            not_deposited = 0
            tempMoney = {
                "200": 0,
                "100": 0,
                "50": 0,
                "20": 0,
                "10": 0,
                "5": 0,
                "2": 0
            }
            print("\nNotas que deseja depositar:\n")
            tempMoney["200"] = int(input("R$200: ") or 0)
            tempMoney["100"] = int(input("R$100: ") or 0)
            tempMoney["50"] = int(input("R$50: ") or 0)
            tempMoney["20"] = int(input("R$20: ") or 0)
            tempMoney["10"] = int(input("R$10: ") or 0)
            tempMoney["5"] = int(input("R$5: ") or 0)
            tempMoney["2"] = int(input("R$2: ") or 0)
            for key in money:
                if tempMoney[key] != 0:
                    while tempMoney[key] > 0:
                        if bank_notes >= MAX_BANK_NOTES:
                            full = True
                            not_deposited += tempMoney[key] * int(key)
                            tempMoney[key] = 0
                            print("\nCaixa lotado")
                            break
                        if not full:
                            money[key] += int(key)
                            users[activeUser]["dinheiro"] += int(key)
                            total_deposited += int(key)
                            bank_notes += 1
                            tempMoney[key] -= 1
                else:
                    money[key] += 0
            tempMoney.clear()
            if not full:
                print("\nDepósito realizado com sucesso")
                print(f"\nTotal depositado: R${total_deposited}")
            else:
                print(
                    "\nQuantia inserida não pode ser depositada, quantia não depositada será retornada")
                print("\nPor favor, contate um funcionário responsável")
                print(f"\nTotal depositado: R${total_deposited}")
                print(f"\nTotal não depositado: R${not_deposited}")
            input("Pressione ENTER para continuar...")
            print("\n")
        elif optionLogged == "2":  # Saque

            withdraw = int(input("\nValor que deseja sacar: "))
            original_withdraw = withdraw

            if withdraw > users[activeUser]["dinheiro"]:
                print(
                    "\nVocê não possui saldo suficiente, se desejar pode fazer um empréstimo")
                input("Pressione ENTER para continuar...")
                print("\n")
            else:
                while withdraw > 0:
                    if withdraw >= 200 and money["200"] > 0:
                        money["200"] -= 1
                        users[activeUser]["dinheiro"] -= 200
                        withdraw -= 200
                        bank_notes -= 1
                    elif withdraw >= 100 and money["100"] > 0:
                        money["100"] -= 1
                        users[activeUser]["dinheiro"] -= 100
                        withdraw -= 100
                        bank_notes -= 1
                    elif withdraw >= 50 and money["50"] > 0:
                        money["50"] -= 1
                        users[activeUser]["dinheiro"] -= 50
                        withdraw -= 50
                        bank_notes -= 1
                    elif withdraw >= 20 and money["20"] > 0:
                        money["20"] -= 1
                        users[activeUser]["dinheiro"] -= 20
                        withdraw -= 20
                        bank_notes -= 1
                    elif withdraw >= 10 and money["10"] > 0:
                        money["10"] -= 1
                        users[activeUser]["dinheiro"] -= 10
                        withdraw -= 10
                        bank_notes -= 1
                    elif withdraw >= 5 and money["5"] > 0:
                        money["5"] -= 1
                        users[activeUser]["dinheiro"] -= 5
                        withdraw -= 5
                        bank_notes -= 1
                    elif withdraw >= 2 and money["2"] > 0:
                        money["2"] -= 1
                        users[activeUser]["dinheiro"] -= 2
                        withdraw -= 2
                        bank_notes -= 1
                    else:
                        print("\nO caixa não possui essa quantidade de notas")
                        print(
                            f"Somente {original_withdraw - withdraw} reais foram sacados")
                        print("Por favor, contate um funcionário responsável")
                        input("Pressione ENTER para continuar...")
                        print("\n")
                        break
        elif optionLogged == "3":  # Saldo
            print("\nSeu saldo é de R$", users[activeUser]["dinheiro"])
            input("Pressione ENTER para continuar...")
            print("\n")
        elif optionLogged == "4":  # Transferência
            target = int(
                input("\nDigite o código do usuário que deseja transferir: "))
            if target > len(users):
                print("\nUsuário não encontrado")
                input("Pressione ENTER para continuar...")
                print("\n")
            elif target == activeUser:
                print("\nVocê não pode transferir para si mesmo")
            else:
                confirm = input(
                    f"Você deseja mesmo transferir para {users[target]['nome']}?(S/N): ").lower().strip()
                if confirm == "s":
                    transferred_money = int(
                        input("\nDigite o valor que deseja transferir: "))
                    if transferred_money > users[activeUser]["dinheiro"]:
                        print("\nVocê não possui saldo suficiente")
                        input("Pressione ENTER para continuar...")
                        print("\n")
                    else:
                        users[activeUser]["dinheiro"] -= transferred_money
                        users[target]["dinheiro"] += transferred_money
                        print(
                            f"\nTransferência realizada com sucesso, {users[target]['nome']} recebeu R${transferred_money}")
                elif confirm == "n":
                    print("\nTransferência cancelada")
                else:
                    print("\nOpção inválida, transferência cancelada")

        elif optionLogged == "5":  # Empréstimo

            loan = int(input("\nQual o valor do empréstimo? "))
            original_loan = loan
            if loan > MAX_LOAN:
                print("\nO valor do empréstimo não pode ser superior a R$", MAX_LOAN)
            elif users[activeUser]["dinheiro"] != 0:
                print("Você ainda possui saldo:",
                      users[activeUser]["dinheiro"], "considere sacá-lo antes de fazer um empréstimo")
                input("Pressione ENTER para continuar...")
                print("\n")
            elif users[activeUser]["dinheiro"] <= -1000:
                print(
                    "\nVocê não pode fazer um empréstimo, seu limite de crédito foi atingido")
            else:
                while loan > 0:
                    if loan >= 200 and money["200"] > 0:
                        money["200"] -= 1
                        users[activeUser]["dinheiro"] -= 200
                        loan -= 200
                        bank_notes -= 1
                    elif loan >= 100 and money["100"] > 0:
                        money["100"] -= 1
                        users[activeUser]["dinheiro"] -= 100
                        loan -= 100
                        bank_notes -= 1
                    elif loan >= 50 and money["50"] > 0:
                        money["50"] -= 1
                        users[activeUser]["dinheiro"] -= 50
                        loan -= 50
                        bank_notes -= 1
                    elif loan >= 20 and money["20"] > 0:
                        money["20"] -= 1
                        users[activeUser]["dinheiro"] -= 20
                        loan -= 20
                        bank_notes -= 1
                    elif loan >= 10 and money["10"] > 0:
                        money["10"] -= 1
                        users[activeUser]["dinheiro"] -= 10
                        loan -= 10
                        bank_notes -= 1
                    elif loan >= 5 and money["5"] > 0:
                        money["5"] -= 1
                        users[activeUser]["dinheiro"] -= 5
                        loan -= 5
                        bank_notes -= 1
                    elif loan >= 2 and money["2"] > 0:
                        money["2"] -= 1
                        users[activeUser]["dinheiro"] -= 2
                        loan -= 2
                        bank_notes -= 1
                    else:
                        print("\nO caixa não possui essa quantidade de notas")
                        print(
                            f"Somente {original_loan - loan} reais foram sacados")
                        print("Por favor, contate um funcionário responsável")
                        input("Pressione ENTER para continuar...")
                        print("\n")
                        break
        elif optionLogged == "8":  # Sair do perfil
            isLogged = False
            activeUser = -1
            print("\nLogout realizado com sucesso")
            input("Pressione ENTER para continuar...")
            print("\n")
        elif optionLogged == "9":  # Sair
            break
