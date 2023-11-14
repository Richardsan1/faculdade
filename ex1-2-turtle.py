import turtle
from time import sleep
# ex 1
def draw_square(color, pos=(0, 0)):
  t = turtle.Turtle()
  t.hideturtle()
  t.penup()
  t.setpos(pos)
  t.pendown()
  t.color(color)
  t.begin_fill()
  
  for i in range(4):
    t.forward(100)
    t.left(90)
  
  t.end_fill()

def draw_retangle(color, sx, sy, pos=(0,0)):
  t = turtle.Turtle()
  t.hideturtle()
  t.penup()
  t.setpos(pos)
  t.pendown()
  t.color(color)
  
  t.begin_fill()

  for i in range(2):
    t.forward(sx)
    t.left(90)
    t.forward(sy)
    t.left(90)
  t.end_fill()

def draw_parallelogram(color, pos=(0,0)):
    t = turtle.Turtle()
    t.hideturtle()
    t.penup()
    t.setpos(pos)
    t.pendown()
    t.color(color)
    t.begin_fill()
    t.forward(200)
    t.left(120)
    t.forward(100)
    t.left(60)
    t.forward(200)
    t.left(120)
    t.forward(100)
    t.end_fill()

# ex 2
def draw_triangle(color, pos=(0,0)):
    t = turtle.Turtle()
    t.hideturtle()
    t.penup()
    t.setpos(pos)
    t.pendown()
    t.color(color)
    t.begin_fill()
    for i in range(3):
        t.forward(100)
        t.left(120)
    t.end_fill()

# ex 3
def draw_house():
    draw_square("#FF8200", (-100, 0))
    draw_retangle("#FFC000", 200, 100, (0, 0))
    draw_triangle("#C0504D", (-100, 100))
    draw_parallelogram("#C00000", (0, 100))
    draw_retangle("#000", 40, 70, (-70, 0))
    draw_retangle("#000", 60, 30, (20, 40))
    draw_retangle("#000", 60, 30, (120, 40))

draw_house()
sleep(20)