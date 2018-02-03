T = input()
while T>0:
    ph = [int(x) for x in raw_input().split()]
    n = ph[0]
    m = ph[1]
    curr1 = curr2 = ans = 0
    last = False
    arr = [int(x) for x in raw_input().split()]
    while n>0:
        ph = arr[n-1]
        if ph>m:
            curr2 += ph
        else:
            if last:
                ans = max(ans, curr2 + curr1 + m)
            curr1 = curr2
            curr2 = 0
            last = (ph == m)
        n -= 1
    T -= 1
    ans = max(ans, curr2 + curr1 + m)
    print ans
