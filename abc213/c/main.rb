h,w,n = gets.split.map(&:to_i)
hh = []
ww = []
for i in 0...n
    a,b = gets.split.map(&:to_i)
    hh << a
    ww << b
end
hhh = hh.dup
www = ww.dup
hh = hh.uniq.sort
ww = ww.uniq.sort
for i in 0...n
    h = hh.bsearch_index{|x| x >= hhh[i]}
    w = ww.bsearch_index{|x| x >= www[i]}
    puts "#{h+1} #{w+1}"
end