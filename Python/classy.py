# Function to convert the string into numbers
def convert(string):
    if string == "upper":
        return 1
    if string == "middle":
        return 2
    # string == "lower"
    return 3


def main():
    numlines = int(input())
    peoplelist = []

    # Scan in the people
    for _ in range(numlines):
        line = input().split(" ")
        name = line[0][:-1]
        level = list(map(convert, line[1].split('-')))
        length = len(level)
        level.reverse()
        level.extend([2]*(10-length))
        peoplelist.append((level, name))

    peoplelist.sort()
    for people in peoplelist:
        print (people[1])

    print ("=" * 30)

# Scan in input
testcases = int(input())
for _ in range(testcases):
    main()
