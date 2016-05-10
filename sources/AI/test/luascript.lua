
io.write("Hello world\n");

testString = "fuck a bitch";

i = 0
for k, v in pairs(map) do
  io.write(v, " ")
  i = i + 1
  if i % map_y == 0 then
    io.write("\n")
  end
end
