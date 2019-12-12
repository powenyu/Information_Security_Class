import random

# RSA 1024


def MillerRabinTest(N):
    if N % 2 == 0:
        return False

    m = N - 1
    k = 0
    while m % 2 == 0:
        k = k + 1
        m = m // 2

    for i in range(5):
        a = random.randrange(2, N - 2)
        b = SquareAndMultiply(a, m, N)
        if b != 1 and b != (N-1):
            i = 1
            while i < k and b != (N-1):
                b = (b * b) % N
                if b == 1:
                    return False
                i = i + 1
            if b != (N-1):
                return False
    return True

# output y = x ^ h mod n


def SquareAndMultiply(x, p, n):
    e = bin(p)
    y = x
    for i in e[3:]:
        y = pow(y, 2) % n
        if i == "1":
            y = (y * x) % n
    return y


def ChineseRemainder(word, d, p, q):
    dp = d % (p - 1)
    m1 = SquareAndMultiply(word, dp, p)
    dq = d % (q - 1)
    m2 = SquareAndMultiply(word, dp, p)
    qInv = ExtendedGCD(p, q)
    if (qInv < 0):
        qInv = p + q
    h = (qInv * (m1 - m2)) % p
    return (m2 + h * q)


def GetPrime():
    temp = False
    while not temp:
        p = random.getrandbits(512)
        temp = MillerRabinTest(p)
    return p


def GCD(a, b):
    if (b == 0):
        return a
    else:
        return GCD(b, a % b)


def ExtendedGCD(a, b):
    old_s, s = 1, 0
    while(b != 0):
        q = a // b
        a, b = b, a - q * b
        old_s, s = s, old_s - q * s
    return old_s


def RSA():
    p = GetPrime()
    q = GetPrime()

    while p == q:
        q = GetPrime()

    n = p * q
    phi = (p - 1) * (q - 1)
    e = random.randrange(1, phi - 1)
    while len(bin(e)[2:]) < 1024:
        e = random.randrange(1, phi - 1)
    while GCD(e, phi) != 1:
        e = random.randrange(1, phi - 1)
        while len(bin(e)[2:]) < 1024:
            e = random.randrange(1, phi - 1)

    d = ExtendedGCD(e, phi)
    if d < 0:
        d = d + phi
    return p, q, n, e, d


def Encrypt(plaintext, e, n):
    output = []
    for word in plaintext:
        temp = SquareAndMultiply(ord(word), e, n)
        output.append(hex(temp)[2:])
    return output


def Decrypt(ciphertext, d, p, q):
    output = ''

    for word in ciphertext:
        temp = ChineseRemainder(int(word, 16), d, p, q)
        output = output + chr(temp)
    return output


if __name__ == '__main__':
    p, q, n, e, d = RSA()
    print("p: ", p)
    print("q: ", q)
    print("n: ", n)
    print("e: ", e)
    print("d: ", d)
    print("Input PlainText:")
    plainText = input()
    cipherText = Encrypt(plainText, e, n)

    print("CipherText: ", cipherText)
    plainText = Decrypt(cipherText, d, p, q)
    print("After Decrypt, Plaintext: ", plainText)
