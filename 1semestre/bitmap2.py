bits = [
    [10],
    [3, 1, 2, 1, 3],
    [2, 6, 2],
    [1, 8, 1],
    [0, 3, 1, 2, 1, 3],
    [0, 1, 1, 6, 1, 1],
    [0, 1, 1, 6, 1, 1],
    [3, 1, 2, 1, 3],
    [2,2,2,2,2],
    [10]
]

for col in bits:
    color = True
    for bit in col:
        if color:
            print(" "*bit, end="")
        else:
            print("*"*bit, end="")
        color = not color
    print()
