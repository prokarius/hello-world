def main():
    testcases = int(input())
    for _ in range(testcases):
        dlist = input().split(" ")
        left = int(dlist[0])
        right = int(dlist[1])
        total = left + right + 1
        print ((total * (total - 1))//2 + 1 + right)

main()
