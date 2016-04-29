//
// SoloButton.cpp for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 14:12:49 2016 maxime liege
// Last update Fri Apr 29 17:02:33 2016 maxime liege
//

#include "PlayerButton.hh"

#include "IAButton.hh"

PlayerButton::PlayerButton(const std::string &name, 
			   const PlayerButton::MODE_PLAYER &id, Menu *menu)
  : _id(id), _name(name)
{
  this->menu = menu;
}

PlayerButton::~PlayerButton()
{

}

void				PlayerButton::action() const
{
  this->menu->clearList();
  this->menu->pushBackList(new IAButton("IA1", IAButton::IA_1, this->menu));
  this->menu->pushBackList(new IAButton("IA2", IAButton::IA_2, this->menu));
  if (this->_id == SOLO)
    this->menu->pushBackList(new IAButton("IA3", IAButton::IA_3, this->menu));
}

bool				PlayerButton::getActive() const
{
  return this->isActive;
}

const std::string		&PlayerButton::getName() const
{
  return this->_name;
}

PlayerButton::MODE_PLAYER	PlayerButton::getId() const
{
  return this->_id;
}
