
local escape = {}

isCellFree = require("isCellFree")

function escape.bombAll()
  return (-1)
end

function escape.bombUpDown()
  if isCellFree.Right() == true then
    return (4)
  end
  return (0)
end

function escape.bombUpDownRight()
  if isCellFree.Left() == true then
    return (3)
  end
  return (0)
end

function escape.bombUpDown()
  if isCellFree.Left() == true then
    return (3)
  elseif isCellFree.Right() == true then
    return (4)
  end
  return (0)
end

function escape.bombUpLeftRight()
  if isCellFree.Down() == true then
    return (2)
  end
  return (0)
end

function escape.bombUpLeft()
  if isCellFree.Down() == true then
    return (2)
  elseif isCellFree.Right() == true then
    return (3)
  end
  return (0)
end

function escape.bombUpRight()
  if isCellFree.Down() == true then
    return (2)
  elseif isCellFree.Left() == true then
    return (3)
  end
  return (0)
end

function escape.bombUp()
  if isCellFree.Right() == true then
    return (4)
  elseif isCellFree.Down() == true then
    return (2)
  elseif isCellFree.Left() == true then
    return (3)
  end
  return (0)
end

function escape.bombDownLeftRight()
  if isCellFree.Up() == true then
    return (1)
  end
  return (0)
end

function escape.bombDownLeft()
  if isCellFree.Up() == true then
    return (1)
  elseif isCellFree.Right() == true then
    return (4)
  end
  return (0)
end

function escape.bombDownRight()
  if isCellFree.Left() == true then
    return (3)
  elseif isCellFree.Up() == true then
    return (1)
  end
  return (0)
end

function escape.bombLeftRight()
  if isCellFree.Up() == true then
    return (1)
  elseif isCellFree.Down() == true then
    return (2)
  end
  return (0)
end

function escape.bombDown()
  if isCellFree.Up() == true then
    return (1)
  elseif isCellFree.Right() == true then
    return (4)
  elseif isCellFree.Left() == true then
    return (3)
  end
  return (0)
end

function escape.bombLeft()
  if isCellFree.Up() == true then
    return (1)
  elseif isCellFree.Down() == true then
    return (2)
  elseif isCellFree.Right() == true then
    return (4)
  end
  return (0)
end

function escape.bombRight()
  if isCellFree.Up() == true then
    return (1)
  elseif isCellFree.Down() == true then
    return (2)
  elseif isCellFree.Left() == true then
    return (3)
  end
  return (0)
end

escape.escapeOptions = {
  escape.bombRight,           -- 1
  escape.bombLeft,            -- 2
  escape.bombLeftRight,       -- 3
  escape.bombDown,            -- 4
  escape.bombDownRight,       -- 5
  escape.bombDownLeft,        -- 6
  escape.bombDownLeftRight,   -- 7
  escape.bombUp,              -- 8
  escape.bombUpRight,         -- 9
  escape.bombUpLeft,          -- 10
  escape.bombUpLeftRight,     -- 11
  escape.bombUpDown,          -- 12
  escape.bombUpDownRight,     -- 13
  escape.bombUpDownLeft,      -- 14
  escape.bombAll              -- 15
}

function escape.tryEscape(choice)
  return (escape.escapeOptions[choice]())
end

return escape

--
-- function bombRight()
--   print("lol")
-- end
--
--
-- function bombLeft()
--   print("haha")
-- end
--
--
-- escapeOptions = {
--   bombRight,
--   bombLeft
-- }
--
-- function tryEscape(choice)
--   escapeOptions[choice]()
-- end
--
-- tryEscape(1)
-- tryEscape(2)
--
