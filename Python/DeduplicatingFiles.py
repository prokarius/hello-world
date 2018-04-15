def cod(n):
    output = {}
    hashed = {}
    out = 0
    for i in range(n):
        textin = input()
        if textin in output.keys():
            output[textin] += 1
        else:
            output[textin] = 1

    for key in output.keys():
        hash = 0
        for i in key:
            hash ^= ord(i)
        if hash in hashed.keys():
            hashed[hash].append(key)
        else:
            hashed[hash] = [key]

    for key, value in hashed.items():
        ph = [output[x] for x in value]
        for i in range(2, len(ph)+1):
            ph[-i] += ph[1-i]

        for i in range(len(ph)-1):
            out += (ph[i] - ph[i+1])*ph[i+1]

    print(len(output), out)

scan = int(input())
while (scan != 0):
    cod(scan)
    scan = int(input())
