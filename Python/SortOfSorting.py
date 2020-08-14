def solve(n):
    # Scan in input
    people = []
    for i in range(n):
        people.append(input())

    # Since sort in python is stable:
    people.sort(key = lambda x: x[0:2])

    print("\n".join(people))

def main():
    n = int(input())
    while n:
        solve(n)
        print()
        n = int(input())

if __name__ == '__main__':
    main()

