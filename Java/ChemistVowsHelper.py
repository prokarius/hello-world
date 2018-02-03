d = []

def two(e):
    return len(e) == 1 and not('*' in e)

for i in range(17):
    n = raw_input()
    k = n.split()
    d.extend(k)

d = filter (two, d)
d.sort()
print '"' + '\", \"'.join(d) + '"'
