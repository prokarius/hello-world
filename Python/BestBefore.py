notleap = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

def code():
    leapyear = False
    if datalist [0] > 12:
        return N + " is illegal"
    if datalist[2] > 31:
        year = (datalist [2] % 2000) + 2000
        if (year %4 == 0) and ((year%100 != 0) or (year%400 == 0)):
            notleap[2] += 1
        if datalist [1] > 12:
            if datalist [1] > notleap [datalist[0]]:
                return N + " is illegal"
        return str(year) + "-" + str(datalist[0]) + "-" + str(datalist[1])
    if datalist [1] > 12:
        month = datalist [0]
        year = (datalist [1] % 2000) + 2000
        if (year %4 == 0) and ((year%100 != 0) or (year%400 == 0)):
            notleap[2] += 1
        day = datalist [2]
        if day > notleap [month]:
            return N + " is illegal"
        return str(year) + "-" + str(month) + "-" + str(day) 
    else:
        year = (datalist [0] % 2000) + 2000
        month = datalist[1]
        day = datalist[2]
        return str(year) + "-" + str(month) + "-" + str(day)
        
N = raw_input()
datalist = [int(x) for x in N.split('/')]
datalist.sort()

print code()

###########
# CORRECT #
###########

def check (y,m,d):
    notleap = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    if (y %4 == 0) and ((y%100 != 0) or (y%400 == 0)):
        notleap[2] += 1
    if ((m > 12) or (d > notleap[m]) or (m == 0) or (d == 0) or (y>2999)):
        return False
    else:
        return True

    
def code():
    for (i,j,k) in ((0,1,2),(0,2,1),(1,0,2),(1,2,0),(2,0,1),(2,1,0)):
        year = (datalist [i] % 2000) + 2000 
        month = datalist [j]
        day = datalist [k]
        if check (year, month, day):
            print str(year) + "-" + str(month).zfill(2) + "-" + str(day).zfill(2)
            return 0
    print N + " is illegal"
            
        
N = raw_input()
datalist = [int(x) for x in N.split('/')]
datalist.sort()
code()
