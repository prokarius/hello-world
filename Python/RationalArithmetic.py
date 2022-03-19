from fractions import Fraction

def solve():
    dlist = input().split(' ')
    a = Fraction(int(dlist[0]), int(dlist[1]))
    b = Fraction(int(dlist[3]), int(dlist[4]))

    if dlist[2] == '+': out = a+b
    elif dlist[2] == '-': out = a-b
    elif dlist[2] == '*': out = a*b
    elif dlist[2] == '/': out = a/b

    print(out.numerator, '/', out.denominator)

def main():
    n = int(input())
    for i in range(n):
        solve()

if __name__ == '__main__':
    main()

