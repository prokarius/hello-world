def solve():
    n = int(input())
    dlist = list(map(int, input().split(" ")))

    count = [0] * 7
    for i in dlist:
        count[i] += 1

    for i in range(6, 0, -1):
        if count[i] == 1:
            print(dlist.index(i) + 1)
            return

    print ("none")
    return

solve()
