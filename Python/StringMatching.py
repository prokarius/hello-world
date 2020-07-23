import sys

# Do KMP
def KMP(text, target):
    length = len(target)

    # Set up target array
    LPS = [0] * length
    i = 1
    prefix = 0

    while (i < length):
        if target[i] == target[prefix]:
            prefix += 1
            LPS[i] = prefix
            i += 1
        elif prefix != 0:
            prefix = LPS[prefix-1]
        else:
            LPS[i] = 0;
            i += 1

    # Do the actual matching
    occurrances = []
    textChar = 0
    targetChar = 0

    while (textChar < len(text)):
        # If the text matches:
        if (text[textChar] == target[targetChar]):
            textChar += 1
            targetChar += 1

            # Check if we found an occurance
            # If we did, append the index of occurance, and reset targetChar using LPS array
            if targetChar == length:
                occurrances.append(textChar - targetChar)
                targetChar = LPS[targetChar - 1]

        # If there is a mismatch: 2 cases:
        # Case 1: We are not at the front of the word:
        # Backtrack to the last occurance of whatever prefix and try again
        elif targetChar != 0:
            targetChar = LPS[targetChar - 1]

        # Case 2: We are at the front of target word:
        # Bummer, just move up the text pointer and start afresh
        else:
            textChar += 1

    # Print all occurrances
    print(" ".join(map(str, occurrances)))

def main():
    target = sys.stdin.readline().rstrip()
    while (target):
        text = sys.stdin.readline()[:-1]
        KMP(text, target)
        target = sys.stdin.readline()[:-1]

if __name__ == '__main__':
    main()

