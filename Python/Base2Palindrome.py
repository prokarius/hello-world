def main():
    n = int(input())
    n -= 1

    # Duct tape
    if n == 0:
        print(1)
        return
    if n == 1:
        print(3)
        return

    length = 1

    # There are (2**(length-1)/2) base 2 palindromes
    while (n >= 2**((length-1)//2)):
        n -= 2**((length-1)//2)
        length += 1

    # Write n in base 2, append a 1 to the front, and mirror it
    base2 = "1" + (str(bin(n))[2:]).zfill((length-1)//2)

    # The middle number is repeated if length is even
    if (length % 2 == 1):
        base2 = base2 + base2[-2::-1]
    else:
        base2 = base2 + base2[::-1]
    print(int(base2, 2))

if __name__ == '__main__':
    main()

