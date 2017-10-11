"""

n = raw_input()
m = raw_input()
x = len(m)

start = 99999999
end = -1

for i in range(x):
    try:
        if n[i] != m[i]:
            start = i
            break
    except (IndexError):
        break

for j in range(x):
    try:
        if n[-j-1] != m[-j-1]:
            end = j
            break
    except (IndexError):
        break

end = x-j

if start >= end:
    print 0
else:
    print end-start

"""
def main ():
    n = raw_input()
    m = raw_input()
    x = len (n)
    y = len (m)
    start = 0
    end = 0

    for i in range(x):
        try:
            if n[i] != m[i]:
                start = i-1
                break
        except IndexError:
            print 0
            return

    if i == x-1:
        print y-x
        return

    for i in range(x-start):
        try:
            if n[x-i-1] != m[y-i-1]:
                end = y-i-1
                break
        except IndexError:
            print y-x
            return
    if i == x-start-1:
        end = y-i-1
            
    print max(end - start,0)

main ()
