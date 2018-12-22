def bits (N):
    maxi = 0
    while N != 0:
        count = 0
        test = str(bin(N))
        for i in test:
            if i == "1":
                count += 1
        if count > maxi:
            maxi = count
        N /= 10
    print maxi

numcase = int(raw_input())
while numcase > 0:
    Q = int(raw_input())
    bits(Q)
    numcase -= 1
