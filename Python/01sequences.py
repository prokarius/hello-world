N = raw_input()
datathing = [0,0,1] #Output, Count of 1, Increment Factor
length = len (N)
for i in range(length):
    if N[(length - i) - 1] == "0":
        datathing [1] += datathing [2]
        datathing [1] = (datathing [1]) % 1000000007
    elif N[(length - i) - 1] == "1":
        datathing [0] = (datathing [0] + datathing [1]) % 1000000007
    else:
        datathing [0] *= 2
        datathing [0] += datathing [1]
        datathing [1] = ((datathing[1] *2) + datathing [2]) % 1000000007
        datathing [2] = (datathing [2] * 2) % 1000000007
    print datathing
        
print datathing [0] % 1000000007
