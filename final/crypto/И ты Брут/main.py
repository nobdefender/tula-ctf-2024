from random import randint
from flag import FLAG

def main(print, input):
    print('Can you pass the _CONDITIONS_? :')
    a = int(input("The first element: "))
    b = int(input("The second element: "))
    print()

    magic_num = 23456789

    # FIRST TRIAL
    if b <= 0:
        print("Not bad, but sad")
        exit(0)

    if pow(magic_num, a - 1, a) != 1:
        print("YOU SHALL NO PASS 1")
        exit(0)

    # SECOND TRIAL
    trial_numbers = [randint(0, 26) for i in range(26)]

    for number in trial_numbers:
        c = a + b * number
        if pow(magic_num, c - 1, c) != 1:
            print("YOU SHALL NO PASS 2")
            exit(0)

    # THIRD TRIAL
    d = a + b * max(trial_numbers)
    if (d.bit_length() < 55):
        print("ACCEPTED")
        print(FLAG)
    else:
        print("YOU SHALL NO PASS 3")