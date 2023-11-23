cifra = input().lower().strip()
mensagem = input().lower().strip()

for i in range(len(mensagem)):
    if mensagem[i] == " ":
        print(" ", end="")
    else:
        print(cifra[ord(mensagem[i]) - 97], end="")
