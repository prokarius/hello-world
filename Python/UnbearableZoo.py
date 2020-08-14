from collections import Counter

def solve(n):
    animals = []

    # Scan in input
    for i in range(n):
        animal = input().split()[-1]
        animals.append(animal.lower())

    # Sort and print
    tuples = list(Counter(animals).items())
    tuples.sort()

    print("\n".join(map(lambda x:f"{x[0]} | {x[1]}", tuples)))


def main():
    n = int(input())
    testcase = 1

    while (n != 0):
        print (f"List {testcase}:")
        testcase += 1

        solve(n)
        n = int(input())

if __name__ == '__main__':
    main()

