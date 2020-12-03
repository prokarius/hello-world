from collections import defaultdict

def main():
    # Scan in input
    n = int(input())

    countries = defaultdict(lambda: list())
    for i in range(n):
        dlist = input().split()
        countries[dlist[0]].append(int(dlist[1]))

    # Sort all the countries
    for k, v in countries.items():
        v.sort()

    # Answer the queries
    q = int(input())

    for i in range(q):
        dlist = input().split()
        print(countries[dlist[0]][int(dlist[1]) - 1])

if __name__ == '__main__':
    main()

