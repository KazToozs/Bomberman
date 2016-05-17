
local isCellFree = {}

function isCellFree.Up()
  if player.y - 1 <= 0 or newMap[player.y - 1][player.x] ~= 0 then
    return (false)
  end
  return (true)
end

function isCellFree.Down()
  if player.y + 1 > map_y or newMap[player.y + 1][player.x] ~= 0 then
    return (false)
  end
  return (true)
end

function isCellFree.Left()
  if player.x - 1 <= 0 or newMap[player.y][player.x - 1] ~= 0 then
    return (false)
  end
  return (true)
end

function isCellFree.Right()
  if player.x + 1 > map_x or newMap[player.y][player.x + 1] ~= 0 then
    return (false)
  end
  return (true)
end

return isCellFree
