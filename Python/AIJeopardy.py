def factorial(lo, hi):
    out = 1
    for i in range(lo, hi+1):
        out *= i
    return out

def choose(n, k):
    return factorial(n - k + 1, n) // factorial(1,  k)

def main():
    x = int(input())

    # Short circuit: If the input is 1, the best you can do is 0 0
    if (x == 1):
        print(0, 0)
        return

    bestN = 10**101
    bestK = 1

    # We try for all possible values of k, and find out what is the smallest value of n.
    # Note that for some value of k, the corresponding value of n that results in the smallest
    # n choose k is 2*k.
    # If we choose a smaller n, then we can reflect k around n/2 to get the same value of n choose k
    # and the k value will then be smaller.

    # Then, we only need to try values of k for (2*k choose k) < 10**100, and this happens at k = 169
    for k in range(1, 170):
        # Do a quick prune. If (2*k choose k is too big for x, we can terminate)
        if (choose(2*k, k) > x):
            break

        # n can be large. Exponential search for n. As noted above, we only need to check for n > 2*k.
        # We can do this because choose(n, k) is ever increasing with n > 2*k.
        potentialN = 4*k
        while (choose(potentialN, k) < x):
            potentialN *= 2

        # Then do binary search here
        hi = potentialN
        lo = potentialN//2

        while (lo <= hi):
            mid = lo + (hi - lo)//2
            tryX = choose(mid, k)
            if (tryX == x):
                if mid < bestN:
                    bestN = mid
                    bestK = k
                break
            if (tryX < x):
                lo = mid + 1
            else:
                hi = mid - 1

    print (bestN, bestK)

if __name__ == '__main__':
    main()

