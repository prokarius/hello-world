testcase = 10000
fibo = [1, 1]
while testcase > 0:
    fibo.append ((fibo[-1] + fibo [-2])%1000000007)
    testcase -= 1

def code (Q):
    print fibo[Q+1]

N = int(raw_input())

counter = 0
while counter < N:
    Q = int(raw_input())
    code(Q)
    counter += 1
