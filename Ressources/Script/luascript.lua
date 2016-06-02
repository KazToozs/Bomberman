
algoMod = require("algo")

player = {x = pos_x, y = pos_y}

newMap = algoMod.makeMap(map, map_x, map_y)
actionChoice = algoMod.getAction()

return actionChoice
