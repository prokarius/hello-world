longest = -1
starting = -1
adjList = []
numImports = 0

def BFS(startNode):
    global starting, longest
    visited = [-1] * numImports
    bfsQueue = [startNode]
    bfsQueueHead = 0
    visited[startNode] = 0

    while(bfsQueueHead < len(bfsQueue)):
        curr = bfsQueue[bfsQueueHead]
        dist = visited[curr]
        bfsQueueHead += 1

        # Push all the neighbours that we have no visited into the queue!
        for neighbour in adjList[curr]:
            if neighbour == startNode:
                if longest < dist + 1:
                    longest = dist + 1
                    starting = startNode
                    return
            if visited[neighbour] != -1: continue
            visited[neighbour] = dist + 1
            bfsQueue.append(neighbour)

def solve():
    global numImports, adjList
    # Scan in input
    numImports = int(input())
    dlist = input().split(" ")

    # Create the hash
    mapping = {}
    revmapping = {}
    for num, val in enumerate(dlist):
        mapping[val] = num
        revmapping[num] = val

    # Create the adjList
    adjList = [list() for _ in range(numImports)]
    for _ in range(numImports):
        dlist = input().split(" ")
        start = mapping[dlist[0]]
        for __ in range(int(dlist[1])):
            ph = input().split(", ")
            ph[0] = ph[0][7:]
            for value in ph:
                adjList[start].append(mapping[value])

    # Do BFS on each of the nodes
    for startNode in range(numImports):
        BFS(startNode)

    # Check if we have found the best
    if (longest == -1):
        print("SHIP IT!")
        return

    # Edge case, if the longest is only 1 long, then print and quit
    if (longest == 1):
        print(revmapping[starting])
        return

    # There is a cycle, do BFS on that node one last time
    visited = [-1] * numImports
    bfsQueue = [starting]
    bfsQueueHead = 0
    visited[starting] = -2
    backtrack = -1

    while(bfsQueueHead < len(bfsQueue)):
        curr = bfsQueue[bfsQueueHead]
        dist = visited[curr]
        bfsQueueHead += 1

        # Push all the neighbours that we have no visited into the queue!
        for neighbour in adjList[curr]:
            if neighbour == starting:
                backtrack = curr
            if visited[neighbour] != -1: continue
            visited[neighbour] = dist + 1
            bfsQueue.append(neighbour)

    # Then backtrack through
    queue = [backtrack]
    while (backtrack != -2):
        queue.append(backtrack)
        backtrack = visited[backtrack]

    # Last, print queue
    print (" ".join([revmapping[num] for num in queue]))

solve()
