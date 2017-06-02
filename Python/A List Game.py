N = int(raw_input())

some_list = [True for i in range(32000)]
some_list[0] = some_list[1] = False;
prime_list = []
for i in range(32000):
    if not some_list[i]:
        continue
    prime_list.append(i)
    for j in range(i,32000/i):
        some_list[j*i] = False

factorisation = []
finished = False
for i in prime_list:
    if N%i == 0:
        counter = 0
        while N%i == 0:
            N = N // i
            counter += 1
        if counter != 0:
            factorisation.append ((i, counter))
        if N == 1:
            finished = True
            break

output = 0    
for i in factorisation:
    output += i[1]

if (N > 32000) and not finished:
    output += 1

print output
