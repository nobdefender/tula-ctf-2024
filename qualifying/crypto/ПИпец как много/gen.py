import math
from Crypto.Util.number import bytes_to_long
import random
import sys
sys.set_int_max_str_digits(maxdigits=8000000)
FLAG = b"TulaCTF{The_DECImAl_DIgitS_Of_PI_ApPear_TO_BE_raNDomlY_DisTRIbUTED}"
flag = bytes_to_long(FLAG)
pi = int(''.join((reversed(''.join(open('pi.txt').read().split())[2:]))))
#pi = int(''.join((reversed(str(math.pi)[2:])))) # 1 десятичный знак дает 1 бит ключа

prec = 1_000_000
while flag:
    bit = flag & 1
    flag = flag >> 1
    r = -1
    while True:
        r = random.randint(0, prec)
        if (pi >> r) & 1 == bit:
            break
    print(r, end=' ')
