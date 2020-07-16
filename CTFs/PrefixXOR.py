from pwn import *
import sys
#sys.setrecursionlimit(1000)

conn = remote('2020.redpwnc.tf', 31458)

print("Set up remote connection")

adjlist = {}

visited = [False]*100001
prefix = [0]*100001

print("Begin reading data")

rawin = []

for i in range(100000):
    raw = conn.recvline().split(" ")
    rawin.append((int(raw[0]), int(raw[1]), int(raw[2])))

print("Emplacing data")

# Emplace
for data in rawin:
    try:
        adjlist[data[0]-1].append((data[1],data[2]))
    except:
        adjlist[data[0]-1] = [(data[1],data[2])]
    try:
        adjlist[data[1]].append((data[0]-1,data[2]))
    except:
        adjlist[data[1]] = [(data[0]-1,data[2])]

print("Scanning Done")

def dfs(k):
    stack = [k]

    while stack:
        i = stack.pop()
        if visited[i]:
            continue
        visited[i] = True
        if i not in adjlist:
            continue
        for edge in adjlist[i]:
            if visited[edge[0]]:
                continue
            prefix[edge[0]] = prefix[i] ^ edge[1]
            stack.append(edge[0])

print("DFS Done")

out = []

for i in range(1, 100001):
    if visited[i]:
        out.append(prefix[i]^prefix[i-1])
    else:
        out.append(0)
        prefix[i] = prefix[i-1]
        dfs(i)

print(prefix[:20])

print("Sending data")
for i in out:
    conn.send(str(i))
    conn.send("\n")
#conn.send(" ".join(map(str, out)))
print("Receiving flag")

print(conn.recvline())
conn.close()
