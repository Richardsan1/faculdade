# convert binario number to octal number
# without using defs

binario = input("Enter a binario number: ")
decimal = 0
digitos = len(binario) - 1

for digito in binario:
    decimal += int(digito) * 2 ** digitos
    digitos -= 1

octal = ""

while decimal > 0:
    octal = str(decimal % 8) + octal
    decimal = decimal // 8
    
print(octal)
