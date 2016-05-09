#include "gui.h"
#include <unistd.h>
#include <iostream>

int main() {
  Gui g;

  g.Start();

  while (g.Alive()) {
    usleep(1000);
    std::cout << std::endl;
  }

  return 0;
}
