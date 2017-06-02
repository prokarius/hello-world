"""

lucklist = [9]
lucknumlist = [1,2,3,4,5,6,7,8,9]
counter = 1
while (lucknumlist) != 0:
    newlucknumlist = []
    counter += 1
    for i in lucknumlist:
        for j in range (10):
            newnum = 10*i + j
            if newnum%counter == 0:
                newlucknumlist.append(newnum)
    lucklist.append(len(newlucknumlist))
    lucknumlist = newlucknumlist

"""

########################

lucklist = [0, 9, 45, 150, 375, 750, 1200, 1713, 2227, 2492, 2492, 2225, 2041, 1575, 1132, 770, 571, 335, 180, 90, 44, 18, 12, 6, 3, 1]
N = int(raw_input())
if N > 25:
    print 0
else:
    print lucklist[N]
