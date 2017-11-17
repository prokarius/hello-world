def basic(n):
    b, p, m = n.split()
    b = int (b)
    x = int(p, b)
    y = int(m, b)
    r = x % y
    o = []
    if r == 0:
        return 0
    while (r):
        o.append(str(r%b))
        r /= b
    return ''.join(o[::-1])

n = raw_input()
while n != '0':
    print basic(n)
    n = raw_input()
