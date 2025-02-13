n = gets.to_i
a = gets.split.map(&:to_i)
aa = [*1..n].zip(a)
aa.sort_by! { |x| x[1] }
puts aa[-2][0]