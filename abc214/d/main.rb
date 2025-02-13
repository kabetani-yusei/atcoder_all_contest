# 木dpを使う
n = gets.to_i
$graph = Array.new(n){[]}
for i in 0...n-1
    u,v,w = gets.split.map(&:to_i)
    $graph[u-1].push([v-1, w])
    $graph[v-1].push([u-1, w])
end
start = -1
for i in 0...n
    if $graph[i].size == 1
        start = i
        break
    end
end
$dp = Array.new(n, -1)
def dfs(v)
    $graph[v].each do |u, w|
        if($dp[u] == -1)
            $dp[u] = dp[v] + w
            $dp[v] += (w + dfs(u))
        end
    end
    return $dp[v]
end
$dp[start] = 0
dfs(start)
puts $dp[start]