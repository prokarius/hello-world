# n = 2: [(1, 2), (2, 1)]
# n = 3:
# ( 1 , 2 ,*3*)
# ( 1 ,*3*, 2 )
# (*3*, 1 , 2 )
# (*3*, 2 , 1 )
# ( 2 ,*3*, 1 )
# ( 2 , 1 ,*3*)

# Solution to recurse
def recurse(n):
    if n == 1:
        return [["1"]]
    out = []
    flag = False
    for i in recurse(n-1):
        if flag:
            for j in range(n):
                toadd = list(i)
                toadd.insert(j, str(n))
                out.append(toadd)
        else:
            for j in range(n-1, -1, -1):
                toadd = list(i)
                toadd.insert(j, str(n))
                out.append(toadd)
        flag = not flag
    return out

def main():
    n = int(input())
    for i in recurse(n):
        print (" ".join(i))

main()
