some_list = [True for i in range(62000)]
some_list[0] = some_list[1] = False;
prime_list = []
for i in range(62000):
    if not some_list[i]:
        continue
    prime_list.append(i)
    for j in range(i,62000/i):
        some_list[j*i] = False

def code(N):
    outputstr = str(N) + ' = '
    number = N
    numtwos = 0
    while N%2 == 0:
        numtwos += 1
        N /= 2
    if N == 1:
        return "IMPOSSIBLE"
    oddnum = 70000
    for i in prime_list:
        if N%i == 0:
            oddnum = i
            break
    if oddnum < (2**(numtwos+1)):
        number /= oddnum
        number -= (oddnum/2)
    else:
        oddnum = 2**(numtwos+1)
        number /= (2**(numtwos+1))
        number -= (2**numtwos)-1
    for i in range(oddnum):
        outputstr += str(number) + " + "
        number += 1
    return outputstr[:-3]

numtest = int(raw_input())
while numtest > 0:
    number = int(raw_input())
    print code(number)
    numtest -= 1
