from Crypto.Util.number import *
import os
from FLAG import flag

class LCG:
    def __init__(self):
        self.m = 128
        self.state = bytes_to_long(os.urandom(1))
        self.a = bytes_to_long(os.urandom(1))
        self.b = bytes_to_long(os.urandom(1))

    def next(self):
        self.state = (self.a * self.state + self.b) % self.m
        return self.state


class RSA:
    BITS = 512

    def __init__(self):
        self.primes = [getPrime(self.BITS) for _ in range(128)]
        self.gen = LCG()

    def encrypt(self, msg):
        p = self.primes[self.gen.next()]
        q = self.primes[self.gen.next()]
        N = p * q
        e = 0x10001
        return (N, e, hex(pow(msg, e, N)))

def main(print, input):
    print("You have 10 queries:")
    print("    1) Encrypt arbitrary message")
    print("    2) Encrypt flag and exit")
    print("")

    print("Initializing service... ")
    cipher = RSA()
    print("DONE!")
    print("")

    for _ in range(10):
        action = input("> ")
        if action == '1':
            message = bytes_to_long(bytes.fromhex(input("Message (hex): ")))
            result = cipher.encrypt(message)
            print(f"Result (N, e, ct): {result}")
        elif action == '2':
            flag_ = bytes_to_long(flag)
            result = cipher.encrypt(flag_)
            print(f"Result (N, e, ct): {result}")
            return 0
    return -1
