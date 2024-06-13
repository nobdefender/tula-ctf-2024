import pwn
pwn.context.log_level = 'error'
while True:
    r = pwn.connect('localhost', 9999)
    r.sendline(b'3')
    r.sendline(b'2')
    print(r.recvall())