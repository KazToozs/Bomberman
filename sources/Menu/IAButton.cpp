//
// IAButton.cpp for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 15:42:47 2016 maxime liege
// Last update Wed May 18 14:10:53 2016 maxime liege
//

#include "IAButton.hh"

IAButton::IAButton(const std::string &name, const NB_IA &id, Menu *menu,
				   bool multi)
	: id(id), name(name) {
	this->multi = multi;
	this->menu = menu;
}

IAButton::~IAButton() {}

Func_Ptr			IAButton::action() const {

	Game	*game;

	game = new Game(id, multi ? 2 : 1, 16, this->menu->getGui());
	this->menu->getGui()->LoadGame(game);
	return &Menu::LaunchGame;
}

const std::string	&IAButton::getName() const {
	return this->name;
}

bool			IAButton::getActive() const {
	return this->isActive;
}

IAButton::NB_IA		IAButton::getId() const {
	return this->id;
}
