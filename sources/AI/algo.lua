
local algo = {}

---------------------------
-- [[ Local variables ]] --
---------------------------

algo.start = {pos_x, pos_y}

---------------------------
-- [[ Various functions ]] --
---------------------------

function algo.helloWorld()
  io.write("Hello world fagoot\n");
end

function algo.makeMap(m, x, y)
  grid = {}
  i = 0
  for y_i = 1, y do
      grid[y_i] = {}
      for x_i = 1, x do
          i = i + 1
          grid[y_i][x_i] = m[i] -- Fill the values here
      end
  end
  return grid

end

algo.newMap = algo.makeMap(map, map_x, map_y)

function algo.getMapValue(x, y)
  return algo.newMap[y][x]
end

function algo.printMap()
  for i = 1, #algo.newMap, 1 do
    for n = 1, #algo.newMap[i] do
      if (algo.newMap[i][n] == 1) then
        io.write("\27[31m", algo.newMap[i][n], " ")
      elseif (algo.newMap[i][n] == 2) then
        io.write("\27[34m", algo.newMap[i][n], " ")
      elseif (algo.newMap[i][n] == 3) then
        io.write("\27[32m", algo.newMap[i][n], " ")
      elseif (algo.newMap[i][n] == 4) then
        io.write("\27[1m", algo.newMap[i][n], "\27[0m ")
      elseif (algo.newMap[i][n] == 5) then
        io.write("\27[93m", algo.newMap[i][n], " ")
      else
        io.write("\27[39m\27[2m", algo.newMap[i][n], "\27[0m ")
      end
    end
    io.write("\27[39m\n");
  end


---------------------
-- [[ Algorithm ]] --
---------------------

function algo.findEnemies()
  local enemies = {}
  for y = 1, #algo.newMap do
    for x = 1, #algo.newMap[y] do
      if (algo.newMap[y][x] == 5) then
        print("Found an enemy: ", x, y)
        enemies.insert({x, y})
      end
    end
  end
  return enemies
end

-- function algo.printEnemies()
--   enemyList = algo.findEnemies()
--   for i = 1, #enemyList do
--     io.write("Enemy ", i, ": ")
--     for n = 1, #enemyList[i] do
--       io.write(enemyList[i][n], " ")
--     end
--   end
-- end
--
-- function algo.algoAlgo()
--   local closedList = {}
--   local openList = {start}
--   local pathList = {}
--
--
-- end

end

return algo
