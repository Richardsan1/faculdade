# Richard Barbosa Sanches - 32385374
# Santiago Ladrón Guevara - 
# Reynaldo - 
from os import system, name

# perimetro da fazenda e da edificação
fazendax1 = None
fazenday1 = None
fazendax2 = None
fazenday2 = None

edificacaox1 = None
edificacaoy1 = None
edificacaox2 = None
edificacaoy2 = None


while True:
    print("""
    -:: Sistema para Análise de Chuva de Meteoros ::-
1. Definir perímetro da propriedade e da edificação de interesse
2. Unificar sistemas de coordenadas de referência
3. Processar registros de chuva de meteoros
4. Apresentar estatísticas
5. Sair
    """)
    option = input("Escolha uma opção: ")
    option = int(option)
    system('cls' if name == 'nt' else 'clear')

    if option == 1:
        print("Definir perímetro da propriedade e da edificação de interesse")
        fazendax1 = int(input("Coordenada x1 da fazenda: "))
        fazenday1 = int(input("Coordenada y1 da fazenda: "))
        fazendax2 = int(input("Coordenada x2 da fazenda: "))
        fazenday2 = int(input("Coordenada y2 da fazenda: "))
        edificacaox1 = int(input("Coordenada x1 da edificação: "))
        edificacaoy1 = int(input("Coordenada y1 da edificação: "))
        edificacaox2 = int(input("Coordenada x2 da edificação: "))
        edificacaoy2 = int(input("Coordenada y2 da edificação: "))
        
        system('cls' if name == 'nt' else 'clear')
        print("Valores salvos com sucesso!")
        input("Pressione ENTER para continuar...")
        system('cls' if name == 'nt' else 'clear')
    
    elif option == 2:
        print("Unificar sistemas de coordenadas de referência")
        system('cls' if name == 'nt' else 'clear')
