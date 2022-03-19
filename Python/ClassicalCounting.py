factorial = {29: [1], 34483: [1]}
inv = {29: [1], 34483: [1]}

# Copied from github
def extended_euclid(a, b):
    if b == 0:
        return (1, 0)
    (x, y) = extended_euclid(b, a % b)
    k = a // b
    return (y, x - k * y)

def crt(n1, r1, n2, r2):
    (x, y) = extended_euclid(n1, n2)
    m = n1 * n2
    n = r2 * x * n1 + r1 * y * n2
    return (n % m + m) % m

# returns a^-1 mod n
def modInv(a, n):
    (b, x) = extended_euclid(a, n)
    if b < 0:
        b = (b % n + n) % n
    return b

def init():
    for mod in [29, 34483]:
        curr = 1
        for i in range(1, mod):
            curr = curr * i % mod
            factorial[mod].append(curr)
            inv[mod].append(modInv(curr, mod))

def _choose(n, k, mod):
    if k > n: return 0
    return (factorial[mod][n] * inv[mod][k] * inv[mod][n-k]) % mod

# Some lucas theorem magic
def choose(n, k):
    output = {}
    for mod in [29, 34483]:
        output[mod] = 1
        _n, _k = n, k
        while (_n > 0 and _k > 0):
            output[mod] = (output[mod] * _choose(_n % mod, _k % mod, mod)) % mod
            _n //= mod
            _k //= mod
    return crt(29, output[29], 34483, output[34483])

def main():
    # Scan in input
    init()
    n, m, k = map(int, input().split())

    # Need to use generating functions. For each object:
    # We have (1 + x + x^2 + ... + x^m) since there is only 1 way to choose i objects
    # = (1 - x^m+1) / (1 - x)
    # We have n of these so (1 - x^m+1)^n * (1 - x)^n
    # The last term expands to (n-1+i choose n-1) * x^i
    total = 0
    sign = 1
    numcount = 0
    while (k >= 0):
        total += sign * choose(n, numcount) * choose((n-1)+k, k)
        k -= m+1
        numcount += 1
        sign *= -1

    print(total % 1000007)

if __name__ == '__main__':
    main()

