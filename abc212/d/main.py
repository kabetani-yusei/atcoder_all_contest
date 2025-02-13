import heapq
q = int(input())
now = []
total = 0
for i in range(q):
    a = [int(read) for read in input().split()]
    if a[0] == 1:
        heapq.heappush(now, a[1]-total)
    elif a[0] == 2:
        total += a[1]
    else:
        print(heapq.heappop(now) + total)