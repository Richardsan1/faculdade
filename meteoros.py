import os

def statistcs():
    return None


perimeter = []
while True:
    # Menu
    # Essa é a interface inicial do programa, sempre que o usuário escolher uma opção, o programa deve limpar a tela e ir para a função.
    print("""
    -:: Sistema para Análise de Chuva de Meteoros ::-
1. Definir perímetro da propriedade e da edificação de interesse
2. Unificar sistemas de coordenadas de referência
3. Processar registros de chuva de meteoros
4. Apresentar estatísticas
5. Sair
    """)
    option = input("Escolha uma opção: ")
    os.system('cls')
    
    # Aqui o programa evita que o usuário digite alguma opção invalida, caso ele digite, o programa deve avisar e voltar para o menu.
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
    elif option == 1: 
        perimeter.append(tuple(input("Digite o ponto 1 (x, y): ")))
        print(perimeter)
        
