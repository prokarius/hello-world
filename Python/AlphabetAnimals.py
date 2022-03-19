from collections import Counter


def main():
    # Scan in input
    curr = input()
    n = int(input())
    words = []
    for i in range(n):
        words.append(input())

    # Populate the dictionary
    countStart = Counter([x[0] for x in words])

    best = None
    for word in words:
        # Continue if it's not a valid word
        if word[0] != curr[-1]: continue

        # Save the first word
        if best is None: best = word

        # If the word does not have a continuation, print it immediately
        if countStart[word[-1]] == 0:
            print(f"{word}!")
            return

        # Or if it starts and ends with the same letter and there is only one count
        if countStart[word[-1]] == 1 and word[0] == word[-1]:
            print(f"{word}!")
            return

    # Right, no definite win. Just say the first ever word then
    if best is None:
        print("?")
    else:
        print(best)

if __name__ == '__main__':
    main()

