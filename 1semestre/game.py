import turtle
import random as r

def Turtlefactory(color, posy):
    objTurtle = turtle.Turtle()
    objTurtle.hideturtle()
    objTurtle.shape("turtle")
    objTurtle.speed(0)
    objTurtle.color(color)
    objTurtle.penup()
    objTurtle.sety(posy)
    objTurtle.setx(-300)
    objTurtle.showturtle()
    objTurtle.pendown()

    return objTurtle

turtles = [
    Turtlefactory("red", 0),
    Turtlefactory("green", 20),
    Turtlefactory("blue", 40),
    Turtlefactory("yellow", 60),
    Turtlefactory("cyan", 80),
]
print("cores: red, green, blue, yellow, cyan")

choice = input("escolha a tartaruga que deseja apostar: ")

endGame = False
victory = False

while True:
    if endGame:
        break
    for t in turtles:
        MovRandom = r.randint(1, 10)
        t.forward(MovRandom)
        if t.pos()[0] >= 250:
            endGame = True
            if t.color()[0] == choice:
                victory = True
    turtle.update()

if victory:
    print("Parabéns! Você acertou.")
else:
    print("Poxa vida! Você errou.")

input("Aperte enter para sair...")