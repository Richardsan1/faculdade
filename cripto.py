letters = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j","k", "l", "m", "n", "o", "p", "q", "r", "s", "t","u", "v", "w", "x", "y", "z"]
key = 4

def encrypt(message, key):
    encrypted_message = []

    for letter in message:
        if letter in letters:
            #find the position of the letter in the alphabet
            position = letters.index(letter)
            #find the new position of the letter with the key
            new_position = (position - key) % 26
            #add the new letter to the encrypted message
            encrypted_message.append(letters[new_position])
        else:
            #if the letter is not in the alphabet add the letter to the encrypted message
            encrypted_message.append(letter)
    #join all letters in the encrypted message
    encrypted_message = "".join(encrypted_message)
    #return the encrypted message
    return encrypted_message

def decrypt(message, key):
    decrypted_message = []

    for letter in message:
        #if the letter is in the alphabet
        if letter in letters:
            #find the position of the letter in the alphabet
            position = letters.index(letter)
            #find the new position of the letter with the key
            new_position = (position + key) % 26
            #add the new letter to the decrypted message
            decrypted_message.append(letters[new_position])
        else:
            #if the letter is not in the alphabet add the letter to the decrypted message
            decrypted_message.append(letter)
    #join all letters in the decrypted message
    decrypted_message = "".join(decrypted_message)
    #return the decrypted message
    return decrypted_message


print(decrypt("XIXK QROFKD BPQX BJ MXAAFKDQLK".lower(), 3))