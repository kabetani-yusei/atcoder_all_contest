n = int(input())
s = [int(read) for read in input().split()]
t = [int(read) for read in input().split()]
for i in range(n*2):
    t[(i+1)%n]=min(t[(i+1)%n],t[i%n]+s[i%n])
for ans in t:
    print(ans)