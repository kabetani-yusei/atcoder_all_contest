n = gets.to_i
a = (n-1).times.map { gets.split.map(&:to_i) }
$graph = Array.new(n) { [] }
a.each do |u, v|
    u -= 1
    v -= 1
    $graph[u] << v
    $graph[v] << u
end
for i in 0...n
    $graph[i].sort!
end
$ans = []
def dfs(now)
    $ans << now+1
    $graph[now].each do |next_v|
        next if $used[next_v]
        $used[next_v] = true
        dfs(next_v)
        $ans << now+1
    end
end
$used = Array.new(n, false)
$used[0] = true
dfs(0)
puts $ans.join(" ")