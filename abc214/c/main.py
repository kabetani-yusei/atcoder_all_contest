import heapq
n = int(input())
s = [int(read) for read in input().split()]
t = [int(read) for read in input().split()]
now = []
for i in range(n):
    if(t[(i+1)%n] > t[i] + s[i]):
        heapq.heappush(now, (t[i] + s[i], (i+1)%n))

while(now):
    time, i = heapq.heappop(now)
    if(t[i] > time):
        t[i] = time
    if(t[(i+1)%n] > time + s[i]):
        heapq.heappush(now, (time + s[i], (i+1)%n))

for i in range(n):
    print(t[i])