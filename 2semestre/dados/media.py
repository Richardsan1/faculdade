import matplotlib.pyplot as p
import random
import math as m

# N1
atv1pt1 = [random.randint(0, 10) for i in range(0, 10)]
atv2pt1 = [random.randint(0, 10) for i in range(0, 10)]
P1 = [random.randint(0, 10) for i in range(0, 10)]

# N2
atv1pt2 = [random.randint(0, 10) for i in range(0, 10)]
atv2pt2 = [random.randint(0, 10) for i in range(0, 10)]
P2 = [random.randint(0, 10) for i in range(0, 10)]

PART = [random.random() for i in range(0, 10)]

media = [0]*10

for i in range(0, 10):
    PART[i] = 0.5 if PART[i] > 0.5 else PART[i]
    med = (((atv1pt1[i] + atv2pt1[i]) / 2) * .3) + (P1[i] * .7)
    med += (((atv1pt2[i] + atv2pt2[i]) / 2) * .3) + (P2[i] * .7)
    med = (med / 2) + PART[i]
    media[m.floor(med)] +=1


p.bar(["0-1", "1-2", "2-3", "3-4", "4-5", "5-6", "6-7", "7-8", "8-9", "9-10"] ,media)

p.title("média dos alunos")
p.show()

