
local isCellFree = {}

function isCellFree.Up(p_y, p_x)

  if (p_x <= 0 or p_y <= 0 or p_x > #newMap[1] or p_y > #newMap) then
    return (false)
  end
  if p_y - 1 <= 0 or newMap[p_y - 1][p_x] ~= 0 then
    return (false)
  end
  return (true)
end

function isCellFree.Down(p_y, p_x)

  if (p_x <= 0 or p_y <= 0 or p_x > #newMap[1] or p_y > #newMap) then
    return (false)
  end
  if p_y + 1 > map_y or newMap[p_y + 1][p_x] ~= 0 then
    return (false)
  end
  return (true)
end

function isCellFree.Left(p_y, p_x)

  if (p_x <= 0 or p_y <= 0 or p_x > #newMap[1] or p_y > #newMap) then
    return (false)
  end
  if p_x - 1 <= 0 or newMap[p_y][p_x - 1] ~= 0 then
    return (false)
  end
  return (true)
end

function isCellFree.Right(p_y, p_x)

  if (p_x <= 0 or p_y <= 0 or p_x > #newMap[1] or p_y > #newMap) then
    return (false)
  end
  if p_x + 1 > map_x or newMap[p_y][p_x + 1] ~= 0 then
    return (false)
  end
  return (true)
end

return isCellFree
