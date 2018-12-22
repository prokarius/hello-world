# For information why this works, visit ThreeDigits.py

def recursion (number):
    if number <= 10:
        lastthreedigits = [0, 1, 2, 6, 4, 2, 2, 4, 2, 8, 8]
        return lastthreedigits [number]
    else:
        leftovers = number % 10
        a = (number/10)-1
        fivefacts = number/5
        threedigits = 1
        while a != 0:
            threedigits *= 4
            threedigits = threedigits %10
            a -= 1
        if leftovers > 4:
            threedigits *= 2
        else:
            threedigits *= 4
        for i in range ((number - leftovers)%10, (number)%10):
            if i % 10 != 4:
                threedigits *= (i+1)
            threedigits = threedigits % 10
        return (threedigits * recursion(fivefacts)) % 10

N = int(raw_input())
while N != 0:
    print recursion (N)
N = int(raw_input())
