from collections import deque

h,w = [int(a) for a in input().split()]
a = [input() for i in range(h)]
dist = [[10**9 for _ in range(w)] for _ in range(h)]
dist[0][0] = 0
now = deque()
now.append((0,0))

# 01bfs
dir = [[1, 0], [-1, 0], [0, 1], [0, -1]]
dir2 = [[1, 0], [-1, 0], [0, 1], [0, -1], [1, 1], [1, -1], [-1, 1], [-1, -1]]
while len(now) > 0:
    x,y = now.popleft()
    for dx, dy in dir:
        nx, ny = x + dx, y + dy
        if(nx < 0 or nx >= h or ny < 0 or ny >= w):
            continue
        elif(a[nx][ny] == '#'):
            for dx2, dy2 in dir2:
                nnx, nny = nx + dx2, ny + dy2
                if(nnx < 0 or nnx >= h or nny < 0 or nny >= w):
                    continue
                if(dist[nnx][nny] > dist[x][y] + 1):
                    dist[nnx][nny] = dist[x][y] + 1
                    now.append((nnx, nny))
        elif(dist[nx][ny] > dist[x][y]):
            dist[nx][ny] = dist[x][y]
            now.appendleft((nx, ny))
            
print(dist[h-1][w-1])