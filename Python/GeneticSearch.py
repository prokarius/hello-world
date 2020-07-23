# Returns the number of matches within the text.
def doKMP(target, text):
    # Generate LPS array from target
    LPS = [0]*len(target)
    i = 1
    prefix = 0

    while (i < len(target)):
        if (target[i] == target[prefix]):
            prefix += 1
            LPS[i] = prefix
            i += 1
        elif (prefix > 0):
            prefix = LPS[prefix-1]
        else:
            LPS[i] = 0
            i += 1

    # Do the actual matching
    textIt = 0
    targetIt = 0

    numMatches = 0

    while (textIt < len(text)):
        if (text[textIt] == target[targetIt]):
            textIt += 1
            targetIt += 1

            if (targetIt == len(target)):
                numMatches += 1
                targetIt = LPS[targetIt - 1]

        elif (targetIt > 0):
            targetIt = LPS[targetIt - 1]

        else:
            textIt += 1

    return numMatches

def solve(string):
    target, text = string.split()

    set2 = set()
    set3 = set()

    # Set 2 is deletion:
    for i in range(len(target)):
        set2.add(target[:i] + target[i+1:])

    # Set 3 is addition
    DNA = ['A', 'T', 'C', 'G']
    for i in range(len(target)+1):
        for base in DNA:
            set3.add(target[:i] + base + target[i:])

    KMP1 = doKMP(target, text)
    KMP2 = KMP3 = 0

    for newTarget in set2:
        KMP2 += doKMP(newTarget, text)

    for newTarget in set3:
        KMP3 += doKMP(newTarget, text)

    print(KMP1, KMP2, KMP3)

def main():
    string = input()
    while (string != '0'):
        solve(string)
        string = input()

if __name__ == '__main__':
    main()

