from itertools import accumulate

def main():
    # Set up powers of 3 and prefixSums of powers of 3
    p3 = [3**x for x in range(20)]
    prefixSums = list(accumulate(p3[:-1]))

    numTests = int(input())

    for _ in range(numTests):
        n = int(input())
        left = []
        right = []

        for i in range(19, 0, -1):
            # Greedy. If the difference is greater than the sums of all previous
            # weights, we can add it in
            if abs(n) > prefixSums[i-1]:
                if n < 0:
                    left.append(p3[i])
                    n += p3[i]
                else:
                    right.append(p3[i])
                    n -= p3[i]

            # If by doing the above we reach balance, we are done.
            if n == 0: break

        # Account for the 1 weight
        if n == 1: right.append(1)
        elif n == -1: left.append(1)

        print(f"left pan: {' '.join(map(str, left))}")
        print(f"right pan: {' '.join(map(str, right))}")
        print()

if __name__ == "__main__":
    main()

