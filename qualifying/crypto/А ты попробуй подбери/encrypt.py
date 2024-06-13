from FLAG import flag


def encrypt(message):
    result = []
    for b in message:
        t1 = (b * 3 + 49) % 256
        t2 = (b ^ 91) + 1
        t3 = (b * 2) - 5
        b = ((t1 + t2 + t3) ^ 231) % 256
        result.append(b)
    return bytes(result)


encrypted_flag = encrypt(flag)

with open("flag.txt.enc", "wb") as file:
    file.write(encrypted_flag)
