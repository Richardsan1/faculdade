def find_mod_inv(a,m):

    for x in range(1,m):
        if((a%m)*(x%m) % m==1):
            return x

a = int(input("valor: "))
m = int(input("modulo: "))

try:
    res=find_mod_inv(a,m)
    print("The required modular inverse is: "+ str(res))

except:
    print('The modular inverse does not exist.')