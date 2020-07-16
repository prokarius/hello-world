# The best split is half-half. If we have more money than $1, just give up
money = float(input())
if money > 1: print(0.25)
else: print((money/2)**2)
