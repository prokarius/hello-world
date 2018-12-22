catalan = [1]
new = 1
for i in range (5000):
    new *= (4*i +2)
    new /= (i+2)
    catalan.append(new)

numcase = int(raw_input())
while numcase > 0:
    Q = int(raw_input())
    print catalan[Q]
numcase -= 1
