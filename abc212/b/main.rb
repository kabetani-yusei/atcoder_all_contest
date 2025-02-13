a = gets.chomp.chars.map(&:to_i)
if(a.uniq.size == 1)
    puts "Weak"
else
    flag = 0
    for i in 0..2
        flag+=1 if(a[i+1] == (a[i]+1) % 10)
    end
    puts flag==3 ? "Weak" : "Strong"
end