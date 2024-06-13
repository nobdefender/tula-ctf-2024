import math
from Crypto.Util.number import bytes_to_long
import random

FLAG = b"TulaCTF{Not_a_flag_hehehehehe}"
MY_PI = ''.join((reversed(str(math.pi)[2:]))) # 1 десятичный знак дает 1 бит ключа

flag = bytes_to_long(FLAG)
pi = int(MY_PI)

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
