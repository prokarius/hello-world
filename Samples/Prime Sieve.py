some_list = [True for i in range(100000)]
some_list[0] = some_list[1] = False;
prime_list = []
for i in range(100000):
    if not some_list[i]:
        continue
    prime_list.append(i)
    for j in range(i,100000/i):
        some_list[j*i] = False


