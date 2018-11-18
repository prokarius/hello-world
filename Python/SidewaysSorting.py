def run(r, c):
    out = []
    grid = [[] for _ in range(c)]
    for rownum in range(r):
        string = input()
        for index, char in enumerate(string):
            grid[index].append(char)

    tosort = [("".join(map(lambda x: x.lower(), grid[x])), x) for x in range(c)]
    tosort.sort()
    for rownum in range(r):
        for col in range(c):
            out.append(grid[tosort[col][1]][rownum])
        out.append("\n")
    print("".join(out[:-1]))

def main():
    dlist = input().split(" ")
    r = int(dlist[0])
    c = int(dlist[1])
    while (r != 0 and c != 0):
        run(r, c)
        dlist = input().split(" ")
        r = int(dlist[0])
        c = int(dlist[1])

main()
