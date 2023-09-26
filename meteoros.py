# Richard Barbosa Sanches - 32385374
# Santiago Ladrón Guevara - 
# Reynaldo - 
from os import system, name

def statistcs():
    return None

def unifyStats(reload=False):
    # essa função deve receber as cordenadas do ponto de referência no plano cartesiano em (x, y)
    cordenadas = ""
    if not reload:
        cordenadas = input("Digite as coordenadas do ponto de referência: ")
        cordenadas = list(map(int, cordenadas.split(",")))
    
    

    return cordenadas

# essa função roda a rotina de coleta de dados de chuva de meteoros
# conforme ela for coletando os dados, ela deve ir adicionando em uma lista
# os dados recebidos são a distância (em metros) e o ângulo do meteoro (em graus)
# a função deve retornar uma lista com os dados coletados

def getMeteors():
    meteors = []
    i = 1
    # pede os dados de cada meteoro até que o usuário digite -1 para a distância
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

# apenas uma função para limpar a tela e manter a legibilidade do programa
clear = lambda : system('cls' if name == 'nt' else 'clear')

# cordenadas da fazenda
perimeter = []
# dados dos meteoros
meteors = []
# ponto de referencia
lab = []

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
    
    # nessa opção o programa deve verificar se o perímetro já foi definido,
    # caso não tenha sido, o programa deve pedir para o usuário definir o perímetro,
    # caso já tenha sido, o programa deve avisar que o perímetro já foi definido e voltar para o menu.
    if option == 1:
        if not perimeter:
            try:
                # aqui o programa pede para o usuário definir o perímetro, caso o usuário digite
                # alguma coisa que não seja um número, o programa deve avisar e voltar para o menu.
                # o perimetro deve ser recebido na forma de x, y

                perimeter.append(list(map(int, input("Digite o ponto 1 do terreno (x, y): ").split(","))))
                perimeter.append(list(map(int, input("Digite o ponto 2 do terreno (x, y): ").split(","))))
                perimeter.append(list(map(int, input("Digite o ponto 1 do edificio (x, y): ").split(","))))
                perimeter.append(list(map(int, input("Digite o ponto 2 do edificio (x, y): ").split(","))))
                unifyStats(True)
                clear()
            except ValueError:
                print("Entrada inválida!")
                continue
        else:
            print("O perímetro da fazenda e da sede já foi definido!")
            input("Pressione ENTER para continuar...")
            clear()
            continue
    elif option == 2:
        lab = unifyStats()

    # roda a função getMeteors e salva os dados dos meteoros
    elif option == 3:
        meteors = getMeteors()
        clear()

    #finaliza o programa
    elif option == 5:
        break

