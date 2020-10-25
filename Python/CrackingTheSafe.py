import queue

bfs = queue.Queue()
seen = set()

def main():
    # Scan in input
    a, b, c = list(map(int, input().split(" ")))
    d, e, f = list(map(int, input().split(" ")))
    g, h, i = list(map(int, input().split(" ")))

    # Do BFS
    bfs.put([(a, b, c, d, e, f, g, h, i) , 0])

    while not bfs.empty():
        curr = bfs.get()
        if curr[0] in seen: continue

        if sum(curr[0]) == 0:
            print(curr[1])
            return

        seen.add(curr[0])
        a = curr[0][0]; b = curr[0][1]; c = curr[0][2]
        d = curr[0][3]; e = curr[0][4]; f = curr[0][5]
        g = curr[0][6]; h = curr[0][7]; i = curr[0][8]

        # Hardcode this
        a1 = ((a+1) % 4, (b+1) % 4, (c+1) % 4, (d+1) % 4, e, f, (g+1) % 4, h, i)
        a2 = ((a+1) % 4, (b+1) % 4, (c+1) % 4, d, (e+1) % 4, f, g, (h+1) % 4, i)
        a3 = ((a+1) % 4, (b+1) % 4, (c+1) % 4, d, e, (f+1) % 4, g, h, (i+1) % 4)
        b1 = ((a+1) % 4, b, c, (d+1) % 4, (e+1) % 4, (f+1) % 4, (g+1) % 4, h, i)
        b2 = (a, (b+1) % 4, c, (d+1) % 4, (e+1) % 4, (f+1) % 4, g, (h+1) % 4, i)
        b3 = (a, b, (c+1) % 4, (d+1) % 4, (e+1) % 4, (f+1) % 4, g, h, (i+1) % 4)
        c1 = ((a+1) % 4, b, c, (d+1) % 4, e, f, (g+1) % 4, (h+1) % 4, (i+1) % 4)
        c2 = (a, (b+1) % 4, c, d, (e+1) % 4, f, (g+1) % 4, (h+1) % 4, (i+1) % 4)
        c3 = (a, b, (c+1) % 4, d, e, (f+1) % 4, (g+1) % 4, (h+1) % 4, (i+1) % 4)

        bfs.put([a1, curr[1]+1])
        bfs.put([a2, curr[1]+1])
        bfs.put([a3, curr[1]+1])
        bfs.put([b1, curr[1]+1])
        bfs.put([b2, curr[1]+1])
        bfs.put([b3, curr[1]+1])
        bfs.put([c1, curr[1]+1])
        bfs.put([c2, curr[1]+1])
        bfs.put([c3, curr[1]+1])

    print(-1)

if __name__ == '__main__':
    main()
