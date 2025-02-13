MOD = 998244353
n,m,k = gets.split.map(&:to_i)
graph = Array.new(n){Array.new()}
for i in 0...m
    u,v = gets.split.map(&:to_i)
    graph[u-1] << v-1
    graph[v-1] << u-1
end
dp = Array.new(n,1)
graph[0].each do |v|
    dp[v] = 0
end
dp[0] = 0
dp2 = Array.new(n)
for _ in 1...k
    total = dp.sum % MOD
    for j in 0...n
        dp2[j] = (total - dp[j]) % MOD
        graph[j].each do |v|
            dp2[j] -= dp[v]
            dp2[j] %= MOD
        end
        dp2[j] %= MOD
    end
    dp = dp2.dup
end
puts dp[0] % MOD
