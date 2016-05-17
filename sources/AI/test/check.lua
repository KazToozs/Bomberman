
function bombRight()
  print("lol")
end


function bombLeft()
  print("haha")
end


escapeOptions = {
  bombRight,
  bombLeft
}

function tryEscape()
  choice = 2
  escapeOptions[choice]()
end

tryEscape(1)
tryEscape(2)
