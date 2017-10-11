"""

### Mark Thng's Question ###

N = input()
x2 = y2 = x = y = xy = 0

for i in range(N):
    a = raw_input()
    dl = [int(k) for k in a.split()]
    x += dl[0]
    y += dl[1]
    xy += dl[0]*dl[1]
    x2 += dl[0]*dl[0]
    y2 += dl[1]*dl[1]

ans = (N*x2*y2-N*xy*xy+2*xy*x*y-x2*y*y-y2*x*x)
q = [".00",".25",".50",".75"]
print str(ans/4)+q[ans%4]+"00"

"""

### More Triangles. Pytha mod n ###

n = int (raw_input())

#TODO:
