def main():
    testcases = int(input())

    for i in range(testcases):
        n, m = list(map(int, input().split(' ')))
        print(n-1)

        for j in range(int(m)):
            input()

if __name__ == '__main__':
    main()

