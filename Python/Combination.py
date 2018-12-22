def code(N):
    output = 120
    comb = [int(x) for x in N.split(" ")]
    output += (comb [0] - comb [1] + 40)%40
    output += (comb [2] - comb [1] + 40)%40
    output += (comb [2] - comb [3] + 40)%40

    print output*9

N = raw_input()

while N != "0 0 0 0":
    code (N)
    N = raw_input()
