# Totally not from geekforgeeks
def modinv(a, m):
    m0 = m
    y = 0
    x = 1

    if (m == 1):
        return 0

    while (a > 1):

        # q is quotient
        q = a // m

        t = m

        # m is remainder now, process
        # same as Euclid's algo
        m = a % m
        a = t
        t = y

        # Update x and y
        y = x - q * y
        x = t


    # Make x positive
    if (x < 0):
        x = x + m0

    return x

def solve():
    dlist = input().split()
    n = int(dlist[0])
    e = int(dlist[1])

    # Bruteforce p and q
    for p in range(2, 1000):
        if (n % p == 0):
            break

    q = n//p
    phi = (p-1)*(q-1)

    d = modinv(e, phi)
    print(d)

def main():
    testcases = int(input())
    for i in range(testcases):
        solve()

if __name__ == '__main__':
    main()

