from Crypto.Util.number import bytes_to_long, getPrime, isPrime
import random
from FLAG import flag

p, q = getPrime(512), 1
while True:
    q = p + random.randint(10_000, 100_000)
    if isPrime(q): break

n = p * q
e = 65537
pt = bytes_to_long(flag)
ct = pow(pt, e, n)

print(f'e = {e}')
print(f'n = {n}')
print(f'ct = {ct}')
