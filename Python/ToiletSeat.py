# Simulate the people putting the seats up and down.
def up(order):
    out = 0
    pos = order[0]
    for i in order[1:]:
        if i != pos:
            out += 1
            pos = i
        if pos == 'D':
            out += 1
            pos = 'U'
    return out

def down(order):
    out = 0
    pos = order[0]
    for i in order[1:]:
        if i != pos:
            out += 1
            pos = i
        if pos == 'U':
            out += 1
            pos = 'D'
    return out

def happy(order):
    out = 0
    pos = order[0]
    for i in order[1:]:
        if i != pos:
            out += 1
            pos = i
    return out

order = input()
print (up(order))
print (down(order))
print (happy(order))
