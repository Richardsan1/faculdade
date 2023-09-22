from os import system, name

def statistcs():
    return None

def unifyStats():
    return None

def getMeteors():
    meteors = []
    i = 1
    while True:
        print(f"Registro #{i}")
        try:
            distance = int(input("-> Distância: "))
            if distance == -1:
                break
            angle = int(input("-> Ângulo: "))
        except ValueError:
            print("Entrada inválida!")
            continue
        meteors.append([distance, angle])
        i+=1
    print(f"Fim da coleta de registros: {len(meteors)} quedas(s) informada(s)")
    input("Pressione ENTER para continuar...")
    return meteors

# apenas uma função para limpar a tela
clear = lambda : system('cls' if name == 'nt' else 'clear')
# cordenadas da fazenda
perimeter = []


while True:
    # Menu
    # Essa é a interface inicial do programa, sempre que o usuário escolher uma opção,
    # o programa deve limpar a tela e ir para a função.
    print("""
    -:: Sistema para Análise de Chuva de Meteoros ::-
1. Definir perímetro da propriedade e da edificação de interesse
2. Unificar sistemas de coordenadas de referência
3. Processar registros de chuva de meteoros
4. Apresentar estatísticas
5. Sair
    """)
    option = input("Escolha uma opção: ")
    clear()

    # Aqui o programa evita que o usuário digite alguma opção invalida,
    # caso ele digite, o programa deve avisar e voltar para o menu.
    try:
        option = int(option)
        if option < 1 or option > 5:
            raise ValueError

    except ValueError:
        print("Opção inválida!")
        continue

    # Aqui o programa verifica qual opção o usuário escolheu e executa a função correspondente.
    if option == 5:
        break
    elif option  == 4:
        statistcs()

    # nessa opção o programa deve verificar se o perímetro já foi definido,
    # caso não tenha sido, o programa deve pedir para o usuário definir o perímetro,
    # caso já tenha sido, o programa deve avisar que o perímetro já foi definido e voltar para o menu.
    elif option == 1:
        if not perimeter:
            try:
                # aqui o programa pede para o usuário definir o perímetro, caso o usuário digite
                # alguma coisa que não seja um número, o programa deve avisar e voltar para o menu.
                # o perimetro deve ser recebido na forma de x, y

                perimeter.append(list(map(int, input("Digite o ponto 1 do terreno (x, y): ").split(","))))
                perimeter.append(list(map(int, input("Digite o ponto 2 do terreno (x, y): ").split(","))))
                perimeter.append(list(map(int, input("Digite o ponto 1 da sede (x, y): ").split(","))))
                perimeter.append(list(map(int, input("Digite o ponto 2 da sede (x, y): ").split(","))))
                clear()
            except ValueError:
                print("Entrada inválida!")
                continue
        else:
            print("O perímetro já foi definido!")
            input("Pressione ENTER para continuar...")
            clear()
            continue
    elif option == 3:
        getMeteors()
        clear()
