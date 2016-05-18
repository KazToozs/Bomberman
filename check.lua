
local check = {}

function check.check_right(m, type)
  local x = pos_x + 1

  while x < pos_x + 4 and x <= #m[pos_y] do
    if m[pos_y][x] == type then
      return (1)
    elseif m[pos_y][x] == 1 or m[pos_y][x] == 2 then
      return (0)
    end
    x = x + 1
  end
  return (0)
end

function check.check_left(m, type)
  local x = pos_x - 1

  while x > pos_x - 4 and x > 0 do
    if m[pos_y][x] == type then
      return (2)
    elseif m[pos_y][x] == 1 or m[pos_y][x] == 2 then
      return (0)
    end
    x = x - 1
  end
  return (0)
end

function check.check_down(m, type)
  local y = pos_y + 1

  while y < pos_x + 4 and y <= #m do
    if m[y][pos_x] == type then
      return (4)
    elseif m[y][pos_x] == 1 or m[y][pos_x] == 2 then
      return (0)
    end
    y = y + 1
  end
  return (0)
end

function check.check_up(m, type)
  local y = pos_y - 1

  while y > pos_x - 4 and y > 0 do
    if m[y][pos_x] == type then
      return (8)
    elseif m[y][pos_x] == 1 or m[y][pos_x] == 2 then
      return (0)
    end
    y = y - 1
  end
  return (0)
end

return check
