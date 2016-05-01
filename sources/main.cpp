#include "gui.h"
#include <unistd.h>

int main() {
    Gui g;

    g.CreateWindow();
    g.SetBackground();
    g.Load();
    while (g.WindowIsOpen()) {
        g.SetBackground();
        usleep(30);
    }

  return 0;
}
