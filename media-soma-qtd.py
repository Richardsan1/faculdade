nums = 0
soma = 0
while True:
    num = int(input())
    if num == -1:
        break
    nums += 1
    soma += num

if nums != 0:
    print(soma)
    print(nums)
    print(soma/nums)
else:
    print('Nenhum número foi digitado!')