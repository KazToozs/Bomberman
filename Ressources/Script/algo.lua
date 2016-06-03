
local algo = {}

local move = require("move")
local check = require("check")
local esc = require("escape")
local isDeadEnd = require("isDeadEnd")

-- move = require("move")
-- check = require("check")
-- esc = require("escape")
-- isDeadEnd = require("isDeadEnd")

---------------------------
-- [[ Local variables ]] --
---------------------------

---------------------------
-- [[ Local functions ]] --
---------------------------

function algo.makeMap(m, x, y)
  grid = {}
  i = 0
  for y_i = 1, y do
      grid[y_i] = {}
      for x_i = 1, x do
          i = i + 1
          grid[y_i][x_i] = m[i]
      end
  end
  return grid
end

-------------------------------
-- [[ Algorithm functions ]] --
-------------------------------

-- Finding enemies

function algo.findEnemies(pos_x, pos_y)
  local enemies = {}
  for i_y = 1, #newMap do
    for i_x = 1, #newMap[i_y] do
      if (newMap[i_y][i_x] == 3) then
        if (i_y ~= pos_y or i_x ~= pos_x) then
          enemies[#enemies + 1] = {x = i_x, y = i_y}
        end
      end
    end
  end
  return enemies
end

-- Enemy Distance

function algo.calculateDistance(en)
  local deltaX = player.x - en.x
  local deltaY = player.y - en.y

  return (math.sqrt(math.pow(deltaX, 2) + math.pow(deltaY, 2)))
end

function algo.findClosestEnemy(enemies)
  local closest = enemies[1]
  local i = 1

  local current = algo.calculateDistance(enemies[1])
  while i <= #enemies do
    local ret = algo.calculateDistance(enemies[i])
    if (current > ret) then
      current = ret
      closest = enemies[i]
    end
    i = i + 1
  end
  return closest
end

-- Base decisions

function algo.isOnBomb()
  local ret

  if (newMap[player.y][player.x] == 4) then
    if isDeadEnd.Right(player.y, player.x) == false then
      return (4)
    elseif isDeadEnd.Left(player.y, player.x) == false then
      return (3)
    elseif isDeadEnd.Down(player.y, player.x) == false then
      return (2)
    elseif isDeadEnd.Up(player.y, player.x) == false then
      return (1)
    end
  else
    return (-1)
  end
end

function algo.isNearBomb()
  local choice = 0

  choice = choice + check.check_up(newMap, 4, player.x, player.y)
  choice = choice + check.check_down(newMap, 4, player.x, player.y)
  choice = choice + check.check_left(newMap, 4, player.x, player.y)
  choice = choice + check.check_right(newMap, 4, player.x, player.y)
  if choice == 0 then
    return (-1)
  else
    return (esc.tryEscape(choice))
  end
end

function algo.isCloseToEnemy()
  local choice = 0
  choice = choice + check.check_up(newMap, 3, player.x, player.y)
  choice = choice + check.check_down(newMap, 3, player.x, player.y)
  choice = choice + check.check_left(newMap, 3, player.x, player.y)
  choice = choice + check.check_right(newMap, 3, player.x, player.y)
  if choice == 0 then
    return (-1)
  else
    return (5)
  end
end

function algo.moveToEnemy()
  local enemies = algo.findEnemies(player.x, player.y)

  if #enemies > 0 then
    local closest = algo.findClosestEnemy(enemies)
    return (move.pickMove(closest))
  else
    return (move.randomMove(player.y, player.x))
  end
end

-- Launch Algorithm

function algo.getAction()
  ret = algo.isNearBomb()
  if (ret == -1) then
    ret = algo.isOnBomb()
    if (ret == -1) then
      ret = algo.isCloseToEnemy()
      if (ret == -1) then
        return (algo.moveToEnemy())
      else
        return (ret)
      end
    else
      return (ret)
    end
  else
    return (ret)
  end
end

return algo
