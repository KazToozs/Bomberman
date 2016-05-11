#include "Gui.hh"
#include <unistd.h>
#include <iostream>

int main() {
  Gui g;

  g.Start();

  while (g.Alive()) {
    usleep(10);
  }

  return 0;
}
