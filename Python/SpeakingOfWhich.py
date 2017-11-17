n = raw_input()
o = 1
vowel = ['a', 'e', 'i', 'o', 'u']
curr = ''
run = 3
vownow = False
for i in n:
    if curr == '':
        if i in vowel:
            continue
        else:
            curr = i
            vownow = True
    elif vownow:
        if i == 'o':
            vownow = False
        else:
            o = (o * (run/2)) % 1000009
            run = 3
            if i in vowel:
                curr = ''
            else:
                curr = i
    else:
        if i == curr:
            run += 1
            vownow = True
        else:
            o = (o * (run/2)) % 1000009
            vownow = False
            run = 3
            if i in vowel:
                curr = ''
            else:
                curr = i
                vownow = True
                
o = (o * (run/2)) % 1000009
print o
