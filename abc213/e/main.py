import heapq
h,w = [int(a) for a in input().split()]
a = [input() for i in range(h)]

now = [(0, 0, 0)]# cost, x, y
used = [[-1 for _ in range(w)] for _ in range(h)]
used[0][0] = 0

# bfsっぽく求める
dir = [[1, 0], [-1, 0], [0, 1], [0, -1]]
dir2 = [[1, 0], [-1, 0], [0, 1], [0, -1], [1, 1], [1, -1], [-1, 1], [-1, -1]]
while(len(now) != 0):
    cost, x, y = heapq.heappop(now)
    if(cost > used[x][y]):
        continue
    for dx, dy in dir:
        nx, ny = x + dx, y + dy
        if(nx < 0 or nx >= h or ny < 0 or ny >= w):
            continue
        elif(a[nx][ny] == '#'):
            for dx2, dy2 in dir2:
                nnx, nny = nx + dx2, ny + dy2
                if(nnx < 0 or nnx >= h or nny < 0 or nny >= w):
                    continue
                if(used[nnx][nny] == -1 or used[nnx][nny] > cost + 1):
                    used[nnx][nny] = cost + 1
                    heapq.heappush(now, (cost + 1, nnx, nny))
        elif(used[nx][ny] == -1 or used[nx][ny] > cost):
            used[nx][ny] = cost
            heapq.heappush(now, (cost, nx, ny))
print(used[h-1][w-1])