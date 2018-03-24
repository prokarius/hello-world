num_lines = int(raw_input())

def code(N):
    data = N.partition(' ')
    cuts = int(data[0])
    words = data[2]
    i = 0
    while i < cuts:
        amount = len(words)//4
        if amount < 1:
            break
        else:
            if i%2 == 0:
                words = words [amount:]
            else:
                words = words [:-amount]
        i += 1
    print words

while num_lines > 0:
    N = raw_input ()
    code (N)
    num_lines -= 1
