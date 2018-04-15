from collections import deque

adjlist = {}
distance = []
parent = []
hash = {}

def main():
    throwaway = input()
    ph = input().split(' ')

    # Set up the hash
    count = 0
    for i in ph:
        hash[i] = count
        count += 1

    # Set up the distance matrix
    distance = [[10000 for x in range(len(ph))] for y in range(len(ph))]
    parent = [[x for x in range(len(ph))] for y in range(len(ph))]

    # Now, generate the adjlist
    for item in ph:
        hashed = hash[item]
        neighbour = []
        dlist = input().split(' ')
        for __ in range(int(dlist[1])):
            phlist = input()[7:].split(", ")
            for item2 in phlist:
                distance[hashed][hash[item2]] = 1

    # Do Floyd Warshall
    for i in range(len(ph)):
        for j in range(len(ph)):
            for k in range(len(ph)):
                if distance[i][j] > distance[i][k] + distance[k][j]:
                    distance[i][j] = distance[i][k] + distance[k][j]
                    parent[i][j] = parent[i][k]

    best = [0, 10000]

    for item in range(len(ph)):
        if best[1] > distance[item][item]:
            best = [item, distance[item][item]]

    # If the number hasn't changed, there is no cycles.
    if best[1] == 10000:
        print ("SHIP IT")
        return

    # There is a cycle
    output = [ph[best[0]]]
    now = parent[best[0]][best[0]]
    while now != best[0]:
        output.append(ph[now])
        now = parent[now][best[0]]

    print (" ".join(output))

main()
