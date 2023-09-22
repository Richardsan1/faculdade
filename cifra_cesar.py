def decrypt(message, key):
    letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    decripted_message = []
    for letter in message:
        if letter in letters:
            position = letters.index(letter)
            new_position = (position - key) % 26
            decripted_message.append(letters[new_position])
        else:
            decripted_message.append(letter)
    decripted_message = "".join(decripted_message)
    return decripted_message

tests = int(input())
decripts = []

for test in range(tests):
    message = input()
    key = int(input())
    decripts.append(decrypt(message, key))

for decript in decripts:
    print(decript)

