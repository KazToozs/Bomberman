
local check = {}

function check.check_right(m, type, p_x, p_y)
  local x = p_x + 1

  if (p_x <= 0 or p_y <= 0 or p_x > #newMap[1] or p_y > #newMap) then
    return (0)
  end
  while x < p_x + 4 and x <= #m[p_y] do
    if m[p_y][x] == type then
      return (1)
    elseif m[p_y][x] == 1 or m[p_y][x] == 2 then
      return (0)
    end
    x = x + 1
  end
  return (0)
end

function check.check_left(m, type, p_x, p_y)
  local x = p_x - 1

  if (p_x <= 0 or p_y <= 0 or p_x > #newMap[1] or p_y > #newMap) then
    return (0)
  end
  while x > p_x - 4 and x > 0 do
    if m[p_y][x] == type then
      return (2)
    elseif m[p_y][x] == 1 or m[p_y][x] == 2 then
      return (0)
    end
    x = x - 1
  end
  return (0)
end

function check.check_down(m, type, p_x, p_y)
  local y = p_y + 1

  if (p_x <= 0 or p_y <= 0 or p_x > #newMap[1] or p_y > #newMap) then
    return (0)
  end
  while y < p_x + 4 and y <= #m do
    if m[y][p_x] == type then
      return (4)
    elseif m[y][p_x] == 1 or m[y][p_x] == 2 then
      return (0)
    end
    y = y + 1
  end
  return (0)
end

function check.check_up(m, type, p_x, p_y)
  local y = p_y - 1

  if (p_x <= 0 or p_y <= 0 or p_x > #newMap[1] or p_y > #newMap) then
    return (0)
  end
  while y > p_x - 4 and y > 0 do
    if m[y][p_x] == type then
      return (8)
    elseif m[y][p_x] == 1 or m[y][p_x] == 2 then
      return (0)
    end
    y = y - 1
  end
  return (0)
end

return check
