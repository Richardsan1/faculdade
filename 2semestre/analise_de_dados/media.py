import matplotlib.pyplot as p
import random
import statistics as stat



# N1
atv1pt1 = [random.randint(0, 10) for i in range(0, 10)]
atv2pt1 = [random.randint(0, 10) for i in range(0, 10)]
P1 = [random.randint(0, 10) for i in range(0, 10)]

# N2
atv1pt2 = [random.randint(0, 10) for i in range(0, 10)]
atv2pt2 = [random.randint(0, 10) for i in range(0, 10)]
P2 = [random.randint(0, 10) for i in range(0, 10)]

PART = [random.random() for i in range(0, 10)]
media = []

for i in range(0, 10):
    PART[i] = 0.5 if PART[i] > 0.5 else PART[i]
    med = (((atv1pt1[i] + atv2pt1[i]) / 2) * .3) + (P1[i] * .7)
    med += (((atv1pt2[i] + atv2pt2[i]) / 2) * .3) + (P2[i] * .7)
    med = (med / 2) + PART[i]
    media.append(med)


p.bar([f"Aluno {i + 1}" for i in range(0, 10)], media)

print(stat.mean(media))

p.title("média dos alunos")
p.show()

