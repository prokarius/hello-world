from collections import Counter

def main():
    names = []
    name = ''

    # Scan in input
    while name != "***":
        name = input()
        names.append(name)

    count = list(Counter(names).items())
    count.sort(key=lambda x: x[1], reverse=True)

    # Check if the name that appears the most doesn't have a tie
    if count[0][1] == count[1][1]: print("Runoff!")
    else: print(count[0][0])

if __name__ == "__main__":
    main()

