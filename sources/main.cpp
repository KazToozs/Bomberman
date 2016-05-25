#include "Gui.hh"
#include <unistd.h>
#include <iostream>
#include "Menu.hh"

int check_keys(Gui &g) {
  static int ret = 0;
  if (g.get_key_event()[irr::KEY_UP].PressedDown) {
    if (ret == 1) usleep(100000);
    ret = 1;
    if (g.get_key_event()[irr::KEY_UP].PressedDown) return (1);
  }
  if (g.get_key_event()[irr::KEY_DOWN].PressedDown) {
    if (ret == 2) usleep(100000);
    ret = 2;
    if (g.get_key_event()[irr::KEY_DOWN].PressedDown) return (2);
  }
  if (g.get_key_event()[irr::KEY_RETURN].PressedDown) {
    if (ret == 3) usleep(100000);
    ret = 3;
    if (g.get_key_event()[irr::KEY_RETURN].PressedDown) return (3);
  }
  ret = 0;
  return (0);
}

int main() {
  Gui g;
  Menu *menu = new Menu(&g);
  int key;
  g.Start(menu);

  while (g.Alive()) {
    key = ((g.getGame() == NULL) ? check_keys(g) : 0);
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
