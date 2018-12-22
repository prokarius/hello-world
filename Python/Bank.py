N = raw_input ()
inputdata = [int(x) for x in N.split ()]
counter = 0
somelist = []
closetime = inputdata [1]
while counter < closetime:
    somelist.append([])
    counter += 1

counter = 0

while counter < inputdata [0]:
    J = raw_input ()
    customer = [int(x) for x in J.split ()]
    (somelist[customer[1]]).append (customer[0])
    counter += 1

for i in somelist:
    i.sort()
    if len(i) > 50:
        i = i [-50:]

sacrifises = []
output = 0
for i in range(closetime):
    for j in somelist[(closetime-i)-1]:
        sacrifises.append(j)
    sacrifises.sort()
    try:
        q = max(sacrifises)
        sacrifises.remove(q)
        output += q
    except (ValueError):
        pass
print output
