# • Elabore um simples jogo de corrida com 5 tartarugas seguindo as definições
# abaixo:
# • Cada tartaruga deve possuir uma cor diferente
# • A velocidade de movimentação de cada tartaruga deve ser aleatória, com valores no intervalo
# de 1 a 10 pixels
# • O jogo deve solicitar ao usuário uma cor de tartaruga na qual ele deseja apostar
# • Defina um ciclo x para executar a corrida, quando a tartaruga tocar a chegada, verifique se o
# usuário acertou, exibindo na tela a mensagem “Parabéns! Você acertou.”, caso o usuário tenha
# errado o palpite, apresenta na tela a mensagem “Poxa vida! Você errou”.

import turtle
import random as r
from time import sleep

def Turtlefactory(color, posy):
    objTurtle = turtle.Turtle()
    objTurtle.hideturtle()
    objTurtle.shape("turtle")
    objTurtle.speed(1)
    objTurtle.color(color)
    objTurtle.penup()
    objTurtle.sety(posy)
    objTurtle.setx(-300)
    objTurtle.showturtle()
    objTurtle.pendown()

    return objTurtle

turtles = [
    Turtlefactory("#F00", 0),
    Turtlefactory("#0F0", 20),
    Turtlefactory("#00F", 40),
    Turtlefactory("#FF0", 60),
    Turtlefactory("#0FF", 80),
]
print("cores: vermelho, verde, azul, amarelo, ciano")

choice = input("escolha a tartaruga que deseja apostar: ")

if choice == "vermelho":
    choice = "#F00"
elif choice == "verde":
    choice = "#0F0"
elif choice == "azul":
    choice = "#00F"
elif choice == "amarelo":
    choice = "#FF0"
else:
    choice = "#0FF"

endGame = False
victory = False

while True:
    if endGame:
        break
    for t in turtles:
        MovRandom = r.randint(1, 10)
        t.forward(MovRandom)
        if t.pos()[0] == 250:
            endGame = True
            if t.color()[0] == choice:
                victory = True
    turtle.update()

if victory:
    print("Parabéns! Você acertou.")
else:
    print("Poxa vida! Você errou.")

sleep(20)