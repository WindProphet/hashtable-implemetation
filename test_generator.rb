require "SecureRandom"
num, infile, outfile = ARGV

num = num.to_i
infile = File.open(infile, "w")
outfile = File.open(outfile, "w")

table = {}

exp = 2.3

num.times do |i|
  puts i if i % 100 == 0
  name = Random.alphanumeric
  val = Random.rand(1<<30)
  table[name] = val
  infile.puts "SET #{name} #{val}"
  s = ((exp+0.5) * 4 * (i+1)*Random.rand/num).to_i
  s.times do |j|
    p = Random.rand
    if p < 0.1
      query = Random.alphanumeric
      infile.puts "GET #{query}"
      outfile.puts "#{query} #{table[query] || "NULL"}"
    elsif p < 0.5
      query = table.keys[Random.rand(table.length)]
      infile.puts "GET #{query}"
      outfile.puts "#{query} #{table[query] || "NULL"}"
    else
      query = table.keys[Random.rand(table.length)]
      nval = Random.rand(1<<30)
      table[query] = nval
      infile.puts "SET #{query} #{nval}"
    end
  end
end

infile.puts "END"
