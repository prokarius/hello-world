def main():
    # Scan in input
    word = input()

    # Place holder best
    best = "|"
    length = len(word)

    # Brute force...?
    for i in range(1, length - 1):
        for j in range(i+1, length):
            piece1 = word[:i]
            piece2 = word[i:j]
            piece3 = word[j:]

            # Make the new word
            piece1 = piece1[::-1]
            piece2 = piece2[::-1]
            piece3 = piece3[::-1]
            newword = "".join([piece1, piece2, piece3])

            # Find the best word
            if (newword < best):
                best = newword

    print (best)

main()
