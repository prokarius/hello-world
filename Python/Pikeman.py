qq = raw_input()
rr = raw_input()
dlist = [int (x) for x in qq.split()]
dlist2 = [int(x) for x in rr.split()]
array = [0 for x in range (100005)]
array2 = [0 for x in range (100005)]

q = dlist2[3]
count = 0
j = 0
out = 0
out2 = 0
curt = 0

while array[q] == 0:
    array[q] = 1
    array2[count] = q
    q = (dlist2[0]*q + dlist2[1])%dlist2[2]+1
    count += 1

while (array2[j] != q):
    j += 1
k = count - j

reps = (dlist[0]-j)/k
rem = (dlist[0]-j)%k

for i in range(j, count):
    array[array2[i]] = reps
    if (i-j < rem):
        array[array2[i]] += 1

i=1
while (dlist[1] > i):
    if (out == dlist[0]):
        break
    ph = min(array[i], dlist[1]/i)
    out += ph
    dlist[1] -= ph*i
    out2 = (out2 + curt*ph + (ph*(ph+1)*i)/2)%1000000007
    curt += ph*i
    i += 1

print str(out), str(out2)

