def main():
    dr = [0,1,0,-1,0]

    dlist = [int(x) for x in input().split()]
    row = dlist[0]
    col = dlist[1]
    grid = []
    for _ in range(row):
        nextrow = input()
        grid.append(nextrow)

    bfs = []
    visited = [[False] * col] * row
    visited[0][0] = True
    length = 1
    head = 0
    bfs.append((0,0,0))
    while head < length:
        curr = bfs[head]
        head += 1
        x = curr[0]
        y = curr[1]
        visited[x][y]
        for i in range (4):
            mag = grid[x][y]
            nextr = x + dr[i]*int(mag)
            if nextr < 0 or nextr >= row:
                continue
            nextc = y + dr[i+1]*int(mag)
            if nextc < 0 or nextc >= col:
                continue
            if visited[nextr][nextc]:
                continue
            if nextr == row-1 and nextc == col-1:
                print (curr[2] + 1)
                return
            bfs.append((nextr, nextc, curr[2]+1))
            length += 1
    print (-1)
    return

main()
