arguments = ["\"","\'", "!", "@", "#", "$", "%", "^", "&", "*"] 
matrix = [False for i in arguments]
print arguments


def code(N):
    for i in N:
        if i in arguments:
            matrix[arguments.index(i)] = True
    


N = raw_input()
while N:
    code (N)
    N = raw_input()
