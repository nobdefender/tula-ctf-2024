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
    "": ""
}

# Function to decrypt the string
# from morse to english
def decrypt(message):

    # extra space added at the end to access the
    # last morse code
    message += " "

    decipher = ""
    citext = ""
    for letter in message:

        # checks for space
        if letter != " ":

            # counter to keep track of space
            i = 0

            # storing morse code of a single character
            citext += letter

        # in case of space
        else:
            # if i = 1 that indicates a new character
            i += 1

            # if i = 2 that indicates a new word
            if i == 2:

                # adding space to separate words
                decipher += " "
            else:

                # accessing the keys using their values (reverse of encryption)
                decipher += list(MORSE_CODE_DICT.keys())[
                    list(MORSE_CODE_DICT.values()).index(citext)
                ]
                citext = ""

    return decipher



from PIL import Image

image = Image.open(r"./moj_pryanik_.png")
width, height = image.size
r, g, b = image.split()
# r = r.point(lambda p: 0xFF if (p & 0b1) == 1 else 0)
# g = g.point(lambda p: 0xFF if (p & 0b1) == 1 else 0)
r = r.point(lambda p: 0)
g = g.point(lambda p: 0)
b = b.point(lambda p: 0xFF if (p & 0b1) == 1 else 0)

image_lsb = Image.merge("RGB", (r, g, b))

print("Do you want see all lsb of blue pixels? (Y/N)")
f=input()
if (f=='Y'):
    image_lsb.show()

startx_pt, starty_pt = 370, 200
endx_pt, endy_pt = 370 + 418, 630
lsb_res = ""
pixels = image.load()
cnt=0
for y in range(starty_pt, endy_pt):
    for x in range(startx_pt, endx_pt):
        r, g, b = pixels[x, y]
        lsb_res += str(b & 0b1)
        cnt+=1
    if cnt==418:
        break 

print(lsb_res)
# may be it's morse?
lsb_res=lsb_res.replace("11110", "-").replace("10", ".").replace("000", " ").strip()
print(lsb_res[1:-1])
print(decrypt(lsb_res[1:-1]))
