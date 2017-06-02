N = raw_input ()
somelist = [int(x) for x in N.split(" ")]

number = somelist [2]
bottles = somelist [0] + somelist [1]
drinks = 0
while bottles > number-1:
    drinks += bottles/number
    bottles -= (bottles/number)*(number-1)
print drinks
