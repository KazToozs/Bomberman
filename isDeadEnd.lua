
local isDeadEnd = {}

local bombRange = 4

function isDeadEnd.getDistanceRight(p_y, p_x)
  local x = p_x
  local count = 0

  while x > 0 and newMap[p_y][x] ~= 4 do
    x = x - 1
    count = count + 1
  end
  return (count)
end

function isDeadEnd.getDistanceLeft(p_y, p_x)
  local x = p_x
  local count = 0

  while x <= #newMap[p_y] and newMap[p_y][x] ~= 4 do
    x = x + 1
    count = count + 1
  end
  return (count)
end

function isDeadEnd.getDistanceUp(p_y, p_x)
  local y = p_y
  local count = 0

  while y <= #newMap and newMap[y][p_x] ~= 4 do
    y = y + 1
    count = count + 1
  end
  return (count)
end

function isDeadEnd.getDistanceDown(p_y, p_x)
  local y = p_y
  local count = 0

  while y > 0 and newMap[y][p_x] ~= 4 do
    y = y - 1
    count = count + 1
  end
  return (count)
end

function isDeadEnd.distanceFromBomb(direction, p_y, p_x)
  if (direction == 1) then -- moving right
    return isDeadEnd.getDistanceRight(p_y, p_x)
  elseif (direction == 2) then -- moving left
    return isDeadEnd.getDistanceLeft(p_y, p_x)
  elseif (direction == 3) then -- moving up
    return isDeadEnd.getDistanceUp(p_y, p_x)
  elseif (direction == 4) then -- moving down
    return isDeadEnd.getDistanceDown(p_y, p_x)
  end
end

function isDeadEnd.Up(p_y, p_x)
  local distance = isDeadEnd.distanceFromBomb(3, p_y, p_x)
  local delta = bombRange - distance
  local safe = p_y - delta
  local i = p_y - 1

  if (p_x <= 0 or p_y <= 0 or p_x > #newMap[1] or p_y > #newMap) then
    return (true)
  end
  while i >= safe and i > 0 do
    if newMap[i][p_x] ~= 0 then
      return true
    elseif i == safe then
      return false
    elseif (p_x - 1 > 0 and newMap[i][p_x - 1]) == 0 or (p_x + 1 <= #newMap[i] and newMap[i][p_x + 1] == 0) then
      return false
    end
    i = i - 1
  end
  return true
end

function isDeadEnd.Right(p_y, p_x)
  print("right")
  local distance = isDeadEnd.distanceFromBomb(1, p_y, p_x)
  local delta = bombRange - distance
  local safe = p_x + delta
  local i = p_x + 1

  if (p_x <= 0 or p_y <= 0 or p_x > #newMap[1] or p_y > #newMap) then
    return (true)
  end
  print("after error check")
  io.write("py: ", p_y )
  io.write("i: ", i)
  while i <= safe and i <= map_x do
    if newMap[p_y][i] ~= 0 then
      print("deadend")
      return true
    elseif i == safe then
      print("safe")
      return false
    elseif (p_y - 1 > 0 and newMap[p_y - 1][i] == 0) or (p_y + 1 <= #newMap and newMap[p_y + 1][i] == 0) then
      print("side")
      return false
    end
    i = i + 1
  end
  print("after while")
  return true
end

function isDeadEnd.Left(p_y, p_x)
  local distance = isDeadEnd.distanceFromBomb(2, p_y, p_x)
  local delta = bombRange - distance
  local safe = p_x - delta
  local i = p_x - 1

  if (p_x <= 0 or p_y <= 0 or p_x > #newMap[1] or p_y > #newMap) then
    return (true)
  end
  while i >= safe and i > 0 do
    if newMap[p_y][i] ~= 0 then
      return true
    elseif i == safe then
      return false
    elseif (p_y + 1 <= #newMap and newMap[p_y + 1][i]) == 0 or (p_y - 1 > 0 and newMap[p_y - 1][i] == 0) then
      return false
    end
    i = i - 1
  end
  return true
end

function isDeadEnd.Down(p_y, p_x)
  local distance = isDeadEnd.distanceFromBomb(4, p_y, p_x)
  local delta = bombRange - distance
  local safe = p_y + delta
  local i = p_y + 1

  if (p_x <= 0 or p_y <= 0 or p_x > #newMap[1] or p_y > #newMap) then
    return (true)
  end
  while i <= safe and i <= #newMap do
    if newMap[i][p_x] ~= 0 then
      return true
    elseif i == safe then
      return false
    elseif (p_x - 1 > 0 and newMap[i][p_x - 1]) == 0 or (p_x + 1 <= #newMap[i] and newMap[i][p_x + 1] == 0) then
      return false
    end
    i = i + 1
  end
  return true
end

return isDeadEnd
