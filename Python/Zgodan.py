def main():
    # Scan in input
    a = input()
    num = int(a)
    a = list(map(int, a))

    parity = a[0] % 2

    # Find where the parity breaks
    for index, curr in enumerate(a):
        if curr % 2 != parity:
            break
        parity = 1 - parity

    larger = list(a[:index]) + [a[index]+1]
    smaller = list(a[:index]) + [a[index]-1]

    num_to_add = parity + (len(a) - index) // 2

    # Generate the larger number by adding 1 to the digit, and then 0101...
    # Generate the smaller number by subtracting 1 from the digit, and then 8989...
    larger += ([1,0] * num_to_add)[parity:]
    smaller += ([9,8] * num_to_add)[parity:]

    # Create the numbers, using try except
    # Duct Tape: Truncate the number to the correct length too.
    try:
        larger = int("".join(list(map(str, larger[:len(a)]))))
    except:
        larger = num*num

    try:
        smaller = int("".join(list(map(str,smaller[:len(a)]))))
    except:
        smaller = num*num

    # Print the closer. There should have been a better way
    diff_larger = abs(num - larger)
    diff_smaller = abs(num - smaller)

    if (diff_larger == diff_smaller):
        print(smaller, larger)
    elif (diff_larger > diff_smaller):
        print(smaller)
    elif (diff_larger < diff_smaller):
        print(larger)


if __name__ == '__main__':
    main()

