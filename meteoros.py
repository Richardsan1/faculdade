# Santiago Guevara - 42333067
# Reynaldo Panella Netto - 42306868
# Richard Barbosa Sanches - 32385374
from os import system, name
import math as m

# perimetro da fazenda e da edificação
fazendax1 = None
fazenday1 = None
fazendax2 = None
fazenday2 = None

edificacaox1 = None
edificacaoy1 = None
edificacaox2 = None
edificacaoy2 = None

# coodenada do lab
labx = None
laby = None

# quedas de meteoro
quedaSede = 0
quedaFaz = 0
# quadrantes de queda
quadNE = 0
quadNO = 0
quadSE = 0
quadSO = 0
# total de quedas
quedas = 0

while True:
    # menu de escolha
    print("""
    -:: Sistema para Análise de Chuva de Meteoros ::-
1. Definir perímetro da propriedade e da edificação de interesse
2. Unificar sistemas de coordenadas de referência
3. Processar registros de chuva de meteoros
4. Apresentar estatísticas
5. Sair
    """)
    # recebe valores entre 1 a 5
    option = int(input("Escolha uma opção: "))
    # limpa a tela
    system('cls' if name == 'nt' else 'clear')

    # delimita o tamanho da fazenda e da edificação
    # pode ser alterado a qualquer momento
    if option == 1:
        print("Definir perímetro da propriedade e da edificação de interesse")
        # as variáveis podem receber valores que pertencem aos numeros racionais
        fazendax1 = float(input("Coordenada x1 da fazenda: "))
        fazenday1 = float(input("Coordenada y1 da fazenda: "))
        fazendax2 = float(input("Coordenada x2 da fazenda: "))
        fazenday2 = float(input("Coordenada y2 da fazenda: "))
        edificacaox1 = float(input("Coordenada x1 da edificação: "))
        edificacaoy1 = float(input("Coordenada y1 da edificação: "))
        edificacaox2 = float(input("Coordenada x2 da edificação: "))
        edificacaoy2 = float(input("Coordenada y2 da edificação: "))

        print("Valores salvos com sucesso!")
        input("Pressione ENTER para continuar...")
        system('cls' if name == 'nt' else 'clear')

    # recebe a coordenada do lab no plano cartesiano
    elif option == 2:
        print("Unificar sistemas de coordenadas de referência")
        # as variáveis podem receber valores que pertencem aos numeros racionais
        labx = float(input("Coordenada x da umpcc: "))
        laby = float(input("Coordenada y da umpcc: "))

        print("Valores salvos com sucesso!")
        input("Pressione ENTER para continuar...")
        system('cls' if name == 'nt' else 'clear')

    # recebe a localização dos meteoros e transforma em coordenadas cartesianas
    elif option == 3:
        # não pode ser acessado caso não tenha sido definido o perímetro da fazenda e da edificação
        if fazendax1 is None:
            print("Impossível processar qualquer registro de queda no momento: localização da propriedade ainda não informada.")
        elif labx is None:
            print("Impossível processar qualquer registro de queda no momento: não foi feita a unificação dos sistemas referenciais usados nos cálculos.")

        # recebe os dados de cada meteoro
        # até que seja digitado -1
        else:
            while True:
                print(f"Registro #{quedas + 1}")
                distancia = float(input("-> Distância: "))
                if distancia == -1:
                    break
                angulo = float(input("-> Ângulo: "))
                # transforma os dados em coordenadas cartesianas
                x = m.cos(m.radians(angulo)) * distancia
                y = m.sin(m.radians(angulo)) * distancia

                # conta a quantidade total de quedas
                quedas += 1

                # verifica se o meteoro caiu dentro da fazenda
                if x > fazendax1 and x < fazendax2 and y > fazenday1 and y < fazenday2:
                    quedaFaz += 1
                    # verifica se o meteoro caiu na edificação
                    if x > edificacaox1 and x < edificacaox2 and y > edificacaoy1 and y < edificacaoy2:
                        quedaSede += 1
                # verifica em qual quadrante o meteoro caiu
                if x > 0:
                    if y > 0:
                        quadNE += 1
                    else:
                        quadSE += 1
                elif x < 0:
                    if y > 0:
                        quadNO += 1
                    else:
                        quadSO += 1

            print(f"Fim da coleta de registros: {quedas} queda(s) informada(s). ")

        input("Pressione ENTER para continuar...")
        system('cls' if name == 'nt' else 'clear')

    # mostra as estatísticas
    elif option == 4:
        # não pode ser acessado caso não tenha sido definido o perímetro da fazenda e da edificação
        # ou caso não tenha sido processado nenhum registro de queda
        if quedas == 0:
            print("Impossivel gerar estatísticas: nenhum registro de queda processado.")

        else:
            print(f"Total de quedas registradas: {quedas} (100%)")
            print(f"Quedas dentro da propriedade: {quedaFaz} ({quedaFaz / quedas * 100:.2f}%)")
            print(f"-> Quadrante NE: {quadNE} ({quadNE / quedas * 100:.2f}%)")
            print(f"-> Quadrante NO: {quadNO} ({quadNO / quedas * 100:.2f}%)")
            print(f"-> Quadrante SO: {quadSO} ({quadSO / quedas * 100:.2f}%)")
            print(f"-> Quadrante SE: {quadSE} ({quadSE / quedas * 100:.2f}%)")
            print(f"A edificação principal foi atingida? {'Sim' if quedaSede > 0 else 'Não'}")

        input("Pressione ENTER para continuar...")
        system('cls' if name == 'nt' else 'clear')
    # fecha o programa
    elif option == 5:
        print("Fim do programa...")
        break
    # caso o valor não esteja no intervalo de 1 a 5
    else:
        print("Opção inválida!")
