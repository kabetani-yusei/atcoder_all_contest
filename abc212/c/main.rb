n,m = gets.chomp.split.map(&:to_i)
a = gets.chomp.split.map(&:to_i)
b = gets.chomp.split.map(&:to_i)
ans = (a[0]-b[0]).abs
a.sort!
b.sort!
for i in 0...n
    c = (0...m).bsearch{|j| b[j] >= a[i]}
    if c != nil
        ans = [ans, (a[i]-b[c]).abs, (a[i]-b[c-1]).abs].min
    else
        ans = [ans, (a[i]-b[m-1]).abs].min
    end
end
puts ans