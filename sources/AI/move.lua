
local move = {}

isCellFree = require("isCellFree")

function move.horizontalMove(deltaX)
  if (deltaX < 0) then
    -- Right
    if (isCellFree.Right() == true) then
      return (4)
    else
      return (5)
    end
  else
    -- left
    if (isCellFree.Left() == true) then
      return (3)
    else
      return (5)
    end
  end
end

function move.verticalMove(deltaY)
  if (deltaY < 0) then
    -- down
    if (isCellFree.Down() == true) then
      return (2)
    else
      return (5)
    end
  else
    -- up
    if (isCellFree.Up() == true) then
      return (1)
    else
      return (5)
    end
  end
end

function move.pickMove(en)
  local deltaX = player.x - en.x
  local deltaY = player.y - en.y
  local absDeltaX = math.abs(deltaX)
  local absDeltaY = math.abs(deltaY)

  if (absDeltaX > absDeltaY) then
    return (move.horizontalMove(deltaX))
  else
    return (move.verticalMove(deltaY))
  end
end

function move.randomMove()
  if (isCellFree.Right() == true) then
    return (4)
  elseif (isCellFree.Left() == true) then
    return (3)
  elseif (isCellFree.Up() == true) then
    return (1)
  elseif (isCellFree.Down() == true) then
    return (2)
  else
    return (0)
  end
end

return move
