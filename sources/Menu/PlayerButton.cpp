//
// SoloButton.cpp for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
//
// Made by maxime liege
// Login   <liege_m@epitech.net>
//
// Started on  Thu Apr 28 14:12:49 2016 maxime liege
// Last update Wed May 18 13:29:47 2016 maxime liege
//

#include "PlayerButton.hh"

#include "IAButton.hh"

PlayerButton::PlayerButton(const std::string &name,
                           const PlayerButton::MODE_PLAYER &id, Menu *menu)
    : _id(id), _name(name) {
  this->menu = menu;
}

PlayerButton::~PlayerButton() {}

Func_Ptr PlayerButton::action() const {
	if (this->_id == MULTI) {
		return &Menu::CreateMultiPlayer;
	}
	else if (this->_id == SOLO) {
		return &Menu::CreateSoloPlayer;
	}
	else
		return NULL;
}

bool PlayerButton::getActive() const { return this->isActive; }

const std::string &PlayerButton::getName() const { return this->_name; }

PlayerButton::MODE_PLAYER PlayerButton::getId() const { return this->_id; }
