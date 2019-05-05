# Essentially, find the maximum gap between the kangaroos
a=input().split()
print(max(int(a[2])-int(a[1]),int(a[1])-int(a[0]))-1)
