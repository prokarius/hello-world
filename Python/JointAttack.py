def GCD(x, y):
    if y == 0:
        return x
    return GCD(y, x%y)

def main():
    dlist = list(map(int, reversed(input().split())))

    # Start from the back, and process each number
    num = dlist[0]
    den = 1

    for x in dlist[1:]:
        num, den = den, num
        num += x*den

    # Simplify the fraction
    gcd = GCD(num, den)

    num //= gcd
    den //= gcd

    print(f"{num}/{den}")

if __name__ == "__main__":
    input() # We technically don't need this line
    main()

