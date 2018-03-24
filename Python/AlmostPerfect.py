import sys

some_list = [True for i in range(32000)]
some_list[0] = some_list[1] = False;
prime_list = []
for i in range(32000):
    if not some_list[i]:
        continue
    prime_list.append(i)
    for j in range(i,32000/i):
        some_list[j*i] = False


def code(N):
    number = N
    factorisation = []
    for i in prime_list:
        if N%i == 0:
            counter = 0
            while N%i == 0:
                N = N // i
                counter += 1
            if counter != 0:
                factorisation.append ((i, counter))
            if N == 1:
                break
    sumfactors = 1
    for i in factorisation:
        sumfactors *= ((1 - i[0]**(i[1]+1))/(1-i[0]))
    sumfactors = abs (sumfactors - 2*number)
    if abs(sumfactors) == 0:
        print str(number) + " perfect"
    elif abs(sumfactors) < 3:
        print str(number) + " almost perfect"
    else:
        print str(number) + " not perfect"

    
N = sys.stdin.readline()

while N:
    code (int(N))
    N = sys.stdin.readline()

