qtdKids = int(input())
allKids = []
behavior = [0, 0]

for i in range(qtdKids):
    kid = input().split(" ")
    if kid[0] == "+":
        behavior[0] += 1
    else:
        behavior[1] += 1
    allKids.append(kid[1])


def orderKids(kids):
  while True:
    changed = False
    for i in range(len(kids)-1):
        if ord(kids[i][0]) > ord(kids[i+1][0]):
            if ord(kids[i][1]) > ord(kids[i+1][1]):
                kids[i], kids[i+1] = kids[i+1], kids[i]
                changed = True
                break
        elif ord(kids[i][0]) > ord(kids[i+1][0]):
            kids[i], kids[i+1] = kids[i+1], kids[i]
            changed = True
            break
    if not changed:
        break
  return kids

allKids = orderKids(allKids)

for kid in allKids:
    print(kid)
print(f"Se comportaram: {behavior[0]} | Nao se comportaram: {behavior[1]}")