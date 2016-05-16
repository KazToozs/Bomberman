#include "Gui.hh"
#include <unistd.h>
#include <iostream>
#include "Menu.hh"

int check_keys(Gui &g) {
    if (g.get_key_event()[irr::KEY_UP].PressedDown) {
        while (g.get_key_event()[irr::KEY_UP].PressedDown)
            usleep(20);
        return (1);
    }
    if (g.get_key_event()[irr::KEY_DOWN].PressedDown) {
        while (g.get_key_event()[irr::KEY_DOWN].PressedDown)
            usleep(20);
        return (2);
    }
    if (g.get_key_event()[irr::KEY_RETURN].PressedDown) {
        while (g.get_key_event()[irr::KEY_RETURN].PressedDown)
            usleep(20);
        return (3);
    }
    return (0);
}

int main() {
  Gui g;
  Menu *menu = new Menu();
  int key;
  g.Start(menu);

  while (g.Alive()) {
    key = check_keys(g);
    switch (key) {
      case 1:
        menu->GoUp();
        break;
      case 2:
        menu->GoDown();
        break;
      case 3:
        menu->Action();
        break;
    }
  }

  return 0;
}
