
local move = {}

isCellFree = require("isCellFree")
isGoodMove = require("isGoodMove")

function move.horizontalMove(deltaX)
  if (deltaX < 0) then
    -- Right
    if (isCellFree.Right(player.y, player.x) == true) then
      if (isGoodMove.Right(player.y, player.x) == true) then
        return (4)
      else
        return (0)
      end
    else
      return (5)
    end
  else
    -- left
    if (isCellFree.Left(player.y, player.x) == true) then
      if (isGoodMove.Left(player.y, player.x) == true) then
        return (3)
      else
        return (0)
      end
    else
      return (5)
    end
  end
end

function move.verticalMove(deltaY)
  if (deltaY < 0) then
    -- down
    if (isCellFree.Down(player.y, player.x) == true) then
      if (isGoodMove.Down(player.y, player.x) == true) then
        return (2)
      else
        return (0)
      end
    else
      return (5)
    end
  else
    -- up
    if (isCellFree.Up(player.y, player.x) == true) then
      if (isGoodMove.Up(player.y, player.x) == true) then
        return (1)
      else
        return (0)
      end
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

function move.randomMove(p_y, p_x)
  if isCellFree.Right(p_y, p_x) == true and isGoodMove.Right(p_y, p_x) == true then
    return (4)
  elseif isCellFree.Left(p_y, p_x) == true and isGoodMove.Left(p_y, p_x) == true then
    return (3)
  elseif isCellFree.Up(p_y, p_x) == true and isGoodMove.Up(p_y, p_x) == true then
    return (1)
  elseif isCellFree.Down(p_y, p_x) == true and isGoodMove.Down(p_y, p_x) == true then
    return (2)
  else
    return (0)
  end
end

return move
