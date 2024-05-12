# Dictionary representing the morse code chart
MORSE_CODE_DICT = {
    "A": ".-",
    "B": "-...",
    "C": "-.-.",
    "D": "-..",
    "E": ".",
    "F": "..-.",
    "G": "--.",
    "H": "....",
    "I": "..",
    "J": ".---",
    "K": "-.-",
    "L": ".-..",
    "M": "--",
    "N": "-.",
    "O": "---",
    "P": ".--.",
    "Q": "--.-",
    "R": ".-.",
    "S": "...",
    "T": "-",
    "U": "..-",
    "V": "...-",
    "W": ".--",
    "X": "-..-",
    "Y": "-.--",
    "Z": "--..",
    "1": ".----",
    "2": "..---",
    "3": "...--",
    "4": "....-",
    "5": ".....",
    "6": "-....",
    "7": "--...",
    "8": "---..",
    "9": "----.",
    "0": "-----",
    ",": "--..--",
    ".": ".-.-.-",
    "?": "..--..",
    "/": "-..-.",
    "-": "-....-",
    "(": "-.--.",
    ")": "-.--.-",
    "_": "..--.-",
}


# Function to encrypt the string
# according to the morse code chart
def encrypt(message):
    cipher = ""
    for letter in message:
        if letter != " ":

            # Looks up the dictionary and adds the
            # corresponding morse code
            # along with a space to separate
            # morse codes for different characters
            # print(letter)
            cipher += MORSE_CODE_DICT[letter] + " "
        else:
            # 1 space indicates different characters
            # and 2 indicates different words
            cipher += " "

    return cipher




from PIL import Image

flag = "PRYANIK_HAS_UNTRULY_FILLING"
flagMorse = encrypt(flag)
# flagBits = (
#     flagMorse.replace(" ", "00100000").replace("-", "00101101").replace(".", "00101110")
# )
flagBits = flagMorse.replace(" ", "000").replace("-", "11110").replace(".", "10")

flagBits = "0000000000000000000000000000" + flagBits + "0000000000000000000000000000"
print(flagMorse)
print(flagBits)
print(len(flagBits))

image = Image.open(r"moj_pryanik.png")
width, height = image.size

# start end points
#####
# for moj_pryanik.jpg
startx_pt, starty_pt = 370, 200
# startx_pt, starty_pt = 0, 0
endx_pt, endy_pt = 370 + 418, 630
# endx_pt, endy_pt = 1200, 800
#####

cnt = 0

pixels = image.load()

# board for morse
for y in range(starty_pt-20,endy_pt+20):
    for x in range(startx_pt, endx_pt):
        r, g, b = pixels[x, y]
        b = b & (0xFF ^ 0b1)
        pixels[x, y] = (r, g, b)

# add morse to lsb
for y in range(starty_pt, min(width, endy_pt),4):
    for x in range(startx_pt, min(height, endx_pt)):
        r, g, b = pixels[x, y]
        if cnt != len(flagBits):
            b = b & (0xFF ^ 0b1)
            b += int(flagBits[cnt])
            cnt += 1
        else:
            cnt = 0
        pixels[x, y] = (r, g, b)
    cnt = 0

image_lsb = image.save("moj_pryanik_.png")
