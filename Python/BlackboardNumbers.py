from fractions import Fraction

somelist = [True for x in range (1050000)]
primelist = []
somelist [0] = somelist[1] = False
for i in range (1050000):
	if somelist[i]:
		primelist.append(i)
		for j in range (i, 1050000/i):
			somelist [i*j] = False

def testo(N):
	if N == 1 or N == 0:
		return 0
	for i in primelist:
		if N == i:
			return 1
		elif N%i == 0:
			return 0
	return 1 


def cod():
	two = eight = ten = sixt = True
	counta = countb = 0	
	N = raw_input()
	for i in range(len(N)):
		a = N[len(N) - i - 1]
		if a in ["A","B","C","D","E","F"]:
			two = eight = ten = False
		elif a in ["9", "8"]:
			two = eight = False
		elif a in ["7", "6", "5", "4", "3", "2"]:
			two = False
	if two:
		Q = int (N, 2)
		counta += testo(Q)
	 	countb += 1
	if eight:
		Q = int (N, 8)
		counta += testo(Q)
		countb += 1
	if ten:
		Q = int (N)
		counta += testo(Q)
		countb += 1
	if sixt:
		Q = int (N, 16)
		counta += testo(Q)
		countb += 1	
	output = Fraction(counta, countb)
	if output == 1:
		output = "1/1" 
	elif output == 0:
		output = "0/1"
	print output


numtest = int(raw_input())
while numtest != 0:
	cod ()
	numtest -= 1
