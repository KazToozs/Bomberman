
local isGoodMove = {}

checker = require("check")

function isGoodMove.inDistanceOfBomb(p_y, p_x)
  print("BBBBBBBBBBBBBBB")
  print("making checks for bomb distance")
  if checker.check_right(newMap, 4, p_x, p_y) == 0
  and checker.check_up(newMap, 4, p_x, p_y) == 0
  and checker.check_down(newMap, 4, p_x, p_y) == 0
  and checker.check_left(newMap, 4, p_x, p_y) == 0 then
    print("returning false for bomb distance")
    return (false)
  else
    print("returning true for bomb distance")
    return (true)
  end
end

function isGoodMove.Up(p_y, p_x)
  print("checking good move up AAAAAAAAAAAAA")
  if isGoodMove.inDistanceOfBomb(p_y - 1, p_x) == true then
    print("returning false")
    return (false)
  else
    print("returning true")
    return (true)
  end
end

function isGoodMove.Down(p_y, p_x)
  if isGoodMove.inDistanceOfBomb(p_y + 1, p_x) == true then
    return (false)
  else
    return (true)
  end
end

function isGoodMove.Left(p_y, p_x)
  if isGoodMove.inDistanceOfBomb(p_y, p_x - 1) == true then
    return (false)
  else
    return (true)
  end
end

function isGoodMove.Right(p_y, p_x)
  if isGoodMove.inDistanceOfBomb(p_y, p_x + 1) == true then
    return (false)
  else
    return (true)
  end
end

return isGoodMove
