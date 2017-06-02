N1 = int(raw_input())
N2 = int(raw_input())
N3 = N2 - N1

if N3 < 0:
    N3 += 360
if N3 > 180:
    N3 -= 360
print N3
