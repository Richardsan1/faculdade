lines = []

while True:
    try:
        line = input()
        line = line.replace('@', 'a')
        line = line.replace('&', 'e')
        line = line.replace('!', 'i')
        line = line.replace('*', 'o')
        line = line.replace('#', 'u')
        lines.append(line)
    
    except EOFError:
        break

for line in lines:
    print(line)
