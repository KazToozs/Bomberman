#include "gui.h"

int main() {
    Gui g;

    g.Create_Window();
    g.Init_Scene();
    g.SetBackground();
    g.Render();
    g.SetText();
}
