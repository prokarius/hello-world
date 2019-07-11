from collections import Counter

def solve():
    word = input()

    # Try out all possible ranges of the word
    for length in range(1, len(word)):
        if len(word) % length != 0: continue
        count = Counter(word[0:length])
        start = length
        flag = True

        # Check each chunk has the required letters
        while start < len(word):
            nextCount = Counter(word[start: start + length])
            if nextCount != count:
                flag = False
                break

            start += length

        if flag:
            print (word[0:length])
            return

    print (-1)

solve()
