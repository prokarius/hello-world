"""
Last 3 non zero digits of n factorial:

So consider splitting the digits by sets of 10.
So you have 10a, 10a +1, 10a + 2, ..., 10a + 9, where a is some integer.

For example, 20! would be the product of all the digits from a = 0 and a = 1.

Note that trailing 0s are given by 2 * 5. Note that in n!, there will be more 2s than 5s in the prime factorization.
So that case, we can pair up numbers that are multiples of 5s with some numbers that are multiples of 2s. 

Given this, we can split each group of 10 into 3 groups: the odd groups, the even groups and the multiples of 5 group:

Odd = (10a +1)(10a +3)(10a + 7)(10a +9)
Even = (10a +2)(10a +4)(10a + 6)(10a +8)
Muls5 = (10a + 5)(10a + 10)

Expand (10a +1)(10a + 3)(10a + 7)(10a + 9):
= 189 + 3000a + 13000a^2 + 20000 a^3 + 10000 a^4
= 189 + 1000(3a + 13a^2 + 20a^3 + 10a^4) 
If you mod this bad boy by 1000 = 189.

~~~

Similarly, we can expand the even group to give:
(10a +2)(10a +4)(10a + 6)(10a +8)
= 384 + 4000a + 14000a^2 + 20000a^3 + 10000a^4 

Now before we mod the above number, we need to pair up two factors of 2 with the numbers from the multiples of 5, so that they form a 10 and therefore can be removed:
= (384 + 4000a + 14000a^2 + 20000a^3 + 10000a^4) / 4
= 96 + 1000a + 3500a^2 + 5000a^3 + 2500a^4
= 96 + 1000a + 1000a^2 + 5000a^3 + 2500a^2 + 2500a^4
= 96 + 1000(a + a^2 + 5a^3) + 2500(a^2)(1+a^2)

Now lets mod this bad boy by 1000; the second term gets removed.

Look at the 3rd term: let a^2 = x.
Then we have (2500)(x)(1+x) % 1000
However, note that since x or 1+x will be even, we therefore know that (x)(1+x) will be even.
Let (x)(1+x) = 2y, y will be an integer, because of the above.
(2500)(x)(1+x) = 2500*2y = 5000y

Therefore, the 3rd term is definitely a multiple of 1000, and therefore will get removed.
Then the product of the even group % 1000 = 96.

~~~

Given this, we realize that no matter what a is, the last 3 nonzero digits of the group (excluding the numbers that are divisible by 5) is (96 * 189) % 1000 = 144.

~~~

Note that we haven't factored the numbers that were divisible by 5 yet. However, suppose we remove a factor of 5 from each of these numbers, we are left with the product of consecutive numbers:

   5  *  10 *  15 *  20 *  25 * ... *  120 *  125
= 5*1 * 5*2 * 5*3 * 5*4 * 5*5 * ... * 5*24 * 5*25
= 5**25 * (1*2*3*4*...*25)
= 5**25 * (25!)

This is just the factorial function! We can therefore define the factorial function recursively!

Now the question is what happens with all the factors of 5 that were pulled out.
Since within each of the groups of 10, we have already paired each of the factors of 5 with a factor of 2 to form 10, we can ignore them.

Therefore we can define a recursive formula:
Last 3 non zero digits of n! = 144**(n/10) * (Last 3 non zero digits of (n/5)!) * leftovers

leftovers refer to the left over numbers that do not form a full group of 10

E.g. in 73!, we can form 7 groups of 10, and the left overs are then 71, 72 and 73.
We can just manually multiply these numbers.

~~~

Now the problem is when to stop the recursion of n!. Well, why not stop when n is <= 10? We can easily compute the factorial for that, and that will form the base case.

"""

### Three Digits ###

def recursion (number):
    if number <= 10:
        lastthreedigits = [0, 1, 2, 6, 24, 12, 72, 504, 32, 288, 288]
        return lastthreedigits [number]
    else:
        leftovers = number % 10
        a = (number/10)-1
        fivefacts = number/5
        threedigits = 1
        while a != 0:
            threedigits *= 144
            threedigits = threedigits %1000
            a -= 1
        if leftovers > 4:
            threedigits *= 72
        else:
            threedigits *= 144
        for i in range ((number - leftovers)%1000, (number)%1000):
            if i % 10 != 4:
                threedigits *= (i+1)
                threedigits = threedigits % 1000
        return (threedigits * recursion(fivefacts)) % 1000

N = int(raw_input())
if N == 8:
    print "032"
elif N < 10:
    print recursion (N)
else:
    T = str(recursion (N) + 1000)
    print T[-3:]


"""
Brute Force Method

Q = int(raw_input())
numFive = 0
numTwo = 0
n = 1
for i in range (1, Q):
    m = i+1

    while ((m%2 == 0) or (m%5 == 0)):
        if m%2 == 0:
            m = m/2
            numTwo += 1
        if m%5 == 0:
            m = m/5
            numFive +=1
    n = (n*m) % 1000

while numFive < numTwo:
    n = n*2 % 1000
    numTwo -= 1

if Q > 7:
    n = str(n+1000)
    print n[-3:]
else:
    numlist = [0, 1, 2, 6, 24, 12, 72, 504]
    print numlist [Q]

"""
"""

### Low Order Zeros ###

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
            threedigits *= 72
        else:
            threedigits *= 144
        for i in range ((number - leftovers)%10, (number)%10):
            if i % 10 != 4:
                threedigits *= (i+1)
            threedigits = threedigits % 10
        return (threedigits * recursion(fivefacts)) % 10
    
N = int(raw_input())
while N != 0:
    print recursion (N)
    N = int(raw_input())


"""
