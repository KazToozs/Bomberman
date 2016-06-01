
-- print("yolo")
algoMod = require("algo")

player = {x = pos_x, y = pos_y}

newMap = algoMod.makeMap(map, map_x, map_y)
actionChoice = algoMod.getAction()
-- io.write("\n-----------\n", "Final choice: ", actionChoice, "\n-----------\n")

return actionChoice
