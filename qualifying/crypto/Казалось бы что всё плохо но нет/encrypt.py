from Crypto.Util.number import getPrime, isPrime, bytes_to_long
from flag import FLAG

FLAG = bytes_to_long(FLAG.encode())

p, q, r = getPrime(512), 1, 1
while not isPrime(p+q):
    q += 1
while not isPrime(p+q+r):
    r += 1

print(f'q: {q}')
print(f'r: {r}')

q = p + q
r = p + q + r

n = p * q * r
e = 2**16 + 1
ct = pow(FLAG, e, n)

print(f'n: {n}')
print(f'e: {e}')
print(f'ct: {ct}')