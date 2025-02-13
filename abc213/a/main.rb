a,b = gets.split.map(&:to_i)
for c in 0..255
    if a ^ c == b
        puts c
        break
    end
end