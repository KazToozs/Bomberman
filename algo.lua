
local algo = {}

move = require("move")
check = require("check")
esc = require("escape")

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

function algo.printMap()
  for i = 1, #newMap, 1 do
    for n = 1, #newMap[i] do
      if (newMap[i][n] == 1) then
        io.write("\27[31m", newMap[i][n], " ")
      elseif (newMap[i][n] == 2) then
        io.write("\27[34m", newMap[i][n], " ")
      elseif (newMap[i][n] == 3) then
        io.write("\27[32m", newMap[i][n], " ")
      elseif (newMap[i][n] == 4) then
        io.write("\27[1m", newMap[i][n], "\27[0m ")
      elseif (newMap[i][n] == 5) then
        io.write("\27[93m", newMap[i][n], " ")
      else
        io.write("\27[39m\27[2m", newMap[i][n], "\27[0m ")
      end
    end
    io.write("\27[39m\n");
  end
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

function algo.printEnemies(enemyList)
  for i = 1, #enemyList do
    io.write("Enemy ", i, ": \n")
    for n = 1, #enemyList[i] do
      io.write(enemyList[i][n], " ")
    end
    io.write("\n")
  end
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

  io.write("Player at x ", player.x, " y ", player.y, "\n")
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
  if (newMap[player.y][player.x] == 4) then
    return (move.randomMove())
  else
    return (-1)
  end
end

function algo.isNearBomb()
  local choice = 0
  choice = choice + check.check_up(newMap, 4)
  choice = choice + check.check_down(newMap, 4)
  choice = choice + check.check_left(newMap, 4)
  choice = choice + check.check_right(newMap, 4)
  if choice == 0 then
    return (-1)
  else
    return (esc.tryEscape(choice))
  end
end

function algo.isCloseToEnemy()
  local choice = 0
  choice = choice + check.check_up(newMap, 3)
  choice = choice + check.check_down(newMap, 3)
  choice = choice + check.check_left(newMap, 3)
  choice = choice + check.check_right(newMap, 3)
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
    io.write("Closest: x: ", closest.x, " y: ", closest.y, "\n")
    -- print("------------------")
    return (move.pickMove(closest))
  else
    return (move.randomMove())
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
