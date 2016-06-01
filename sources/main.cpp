#include "Gui.hh"
#include <cstdlib>
#include <chrono>
#include <thread>
#include <iostream>
#include "Menu.hh"

int check_keys(Gui &g) {
	static int ret = 0;
	if (g.get_key_event()[irr::KEY_UP].PressedDown) {
		if (ret == 1) std::this_thread::sleep_for(std::chrono::microseconds(100000));
		ret = 1;
		if (g.get_key_event()[irr::KEY_UP].PressedDown) return (1);
	}
	if (g.get_key_event()[irr::KEY_DOWN].PressedDown) {
		if (ret == 2) std::this_thread::sleep_for(std::chrono::microseconds(100000));
		ret = 2;
		if (g.get_key_event()[irr::KEY_DOWN].PressedDown) return (2);
	}
	if (g.get_key_event()[irr::KEY_RETURN].PressedDown) {
		if (ret == 3) std::this_thread::sleep_for(std::chrono::microseconds(100000));
		ret = 3;
		if (g.get_key_event()[irr::KEY_RETURN].PressedDown) return (3);
	}
	ret = 0;
	return (0);
}

Func_Ptr MenuBtnTab[] = {
	&Menu::GoUp,
	&Menu::GoDown,
	&Menu::Action,
	NULL
};

int main() {
	Gui g;
	Menu *menu = new Menu(&g);
	int key;
	g.Start(menu);
	bool start = false;

	while (g.Alive()) {
		if (!start) {
			g.LoadGame(new Game(0, 2, 16, &g));
			start = true;
		}
		/*
		key = ((g.getGame() == NULL) ? check_keys(g) : 0);
		if (key)
			(menu->*MenuBtnTab[key - 1])();
			*/
	}

	return 0;
}
