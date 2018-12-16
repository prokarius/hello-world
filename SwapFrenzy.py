def gen_swaps(x, numswaps):
    if numswaps == 0:
        yield x
        return
    tried_dup_swap = False
    is_sorted = all(i >= j for i, j in zip(x, x[1:]))
    for i in range(len(x)):
        for j in range(i+1, len(x)):
            y = x[:]
            y[i], y[j] = y[j], y[i]
            if y[i] == y[j]:
                if tried_dup_swap:
                    continue
                tried_dup_swap = True
            if y[i] < y[j] and not is_sorted:
                continue
            yield from gen_swaps(y, numswaps-1)

def brutey(xs, numswaps):
    return max(i for i in gen_swaps(xs, numswaps))

def fuzz(method):
    import random

    while True:
        x = [random.choice('0123456789') for _ in range(7)]
        for i in range(7):
            brute = brutey(x, i)
            answer = method(x, i)
            print(''.join(x), i, brute == answer, ''.join(brute), ''.join(answer))
            if brute != answer:
                return

def swapfrenzy(n, k)
    # Make the target list
    nsorted = list(n)
    nsorted.sort()
    nsorted.reverse()

    # If we have more swaps than necessary
    if k >= len(n) - 1:
        if (k - len(n)) % 2:
            print (''.join(nsorted))
        else:
            print (''.join(nsorted[:-2]+nsorted[-1:]+nsorted[-2:-1]))
        return

    # OK we have less than necessary. So we will do the greedy solution
    # For each value of k
    currentIndex = 0
    alreadySorted = False

    while k and not alreadySorted:
        if currentIndex > len(n):
            alreadySorted = True
            continue
        if (n[currentIndex] == nsorted[currentIndex]):
            currentIndex += 1
        
    # OK here we would have broken out of the main loop, this means
    if (alreadySorted):


def main():
    # Scan in the input
    n, k = input().split(' ')
    n = list(n)
    k = int(k)

    # run() method
    swapFrenzy(n, k)

fuzz(swapFrenzy)
