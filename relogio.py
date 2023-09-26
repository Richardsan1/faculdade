horario = list(map(int, input("Digite o horário (hh:mm): ").split(":")))

hora = '{0:05b}'.format(horario[0])
minuto = '{0:06b}'.format(horario[1])

print(chr(95)*53)

for i in range(13):
    print(chr(124), " "*6, end="")
    
    if i == 0:
        print(chr(95)*37, end="")
    
   
    elif i == 3:
        print(chr(124), end="")
        print("    32     8     4     2     1     ", end="")
        print(chr(124), end="")

    elif i == 4:
        print(chr(124), end="")
        print("      ", end="") if hora[0] == "0" else print("    ", chr(248), end="")
        print("      ", end="") if hora[1] == "0" else print("    ", chr(248), end="")
        print("      ", end="") if hora[2] == "0" else print("    ", chr(248), end="")
        print("      ", end="") if hora[3] == "0" else print("    ", chr(248), end="")
        print("           ", end="") if hora[4] == "0" else print("     {}     ".format(chr(248)), end="")
        
        print(chr(124), end="")
    
    elif i == 7:
        print(chr(124), end="")
        print("     ", end="") if minuto[0] == "0" else print("   ", chr(248), end="")
        print("     ", end="") if minuto[1] == "0" else print("   ", chr(248), end="")
        print("     ", end="") if minuto[2] == "0" else print("   ", chr(248), end="")
        print("     ", end="") if minuto[3] == "0" else print("   ", chr(248), end="")
        print("     ", end="") if minuto[4] == "0" else print("   ", chr(248), end="")
        print("          ", end="") if minuto[5] == "0" else print("    {}     ".format(chr(248)), end="")
        
        print(chr(124), end="")

    elif i == 8:
        print(chr(124), end="")
        print("   64   32    8    4    2    1     ", end="")
        print(chr(124), end="")
    
    elif i == 12:
        print("‾"*37, end="")
    
    else: 
        print(chr(124), " "*34, end="")
        print(chr(124), end="")

    print(" "*6, chr(124), end="\n")

print("‾"*53)