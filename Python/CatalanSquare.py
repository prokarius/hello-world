catalan = [1]
new = 1
for i in range (5001):
    new *= (4*i +2)
    new /= (i+2)
    catalan.append(new)

numcase = int(raw_input())
output = 0
for i in range(numcase+1):
    output += catalan[i]*catalan[numcase-i]

print output
