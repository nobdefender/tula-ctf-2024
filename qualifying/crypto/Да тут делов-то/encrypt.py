from Crypto.Util.number import bytes_to_long, getPrime
from FLAG import flag

n = 1
for _ in range(100): n *= getPrime(20)
e = 65537
pt = bytes_to_long(flag)
ct = pow(pt, e, n)

print(f'e = {e}')
print(f'n = {n}')
print(f'ct = {ct}')
