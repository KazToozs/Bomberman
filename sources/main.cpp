#include "gui.h"
#include <unistd.h>
#include <iostream>

int main() {
  Gui g;

  g.Start();

  while (g.Alive()) {
    usleep(1000);
    if (g.get_joy_event().Axis[1] < 0.2f)
        g.SetText("Up !");
    if (g.get_joy_event().Axis[1] > 0.2f)
        g.SetText("Down !");
    if (g.get_joy_event().Axis[1] == 0)
        g.SetText("Solo");
  }

  return 0;
}
