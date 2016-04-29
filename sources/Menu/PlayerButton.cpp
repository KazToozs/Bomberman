//
// SoloButton.cpp for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 14:12:49 2016 maxime liege
// Last update Thu Apr 28 18:41:31 2016 maxime liege
//

#include "PlayerButton.hh"

PlayerButton::PlayerButton(const std::string &name, const MODE_PLAYER &id, Menu *menu)
  : name(name), id(id)
{
  this->menu = menu;
}

PlayerButton::~PlayerButton()
{

}

void		PlayerButton::action() const
{
  this->menu->clearList();
  this->menu->pushBackList(new IAButton(IAButton::IA_1, "IA1", this->menu));
  this->menu->pushBackList(new IAButton(IAButton::IA_2, "IA2", this->menu));
  if (this->id == SOLO)
    this->menu->pushBackList(new IAButton(IAButton::IA_3, "IA3", this->menu));
}

bool		PlayerButton::getActive() const
{
  return this->isActive;
}

std::string	PlayerButton::getName() const
{
  return this->name;
}

const short	PlayerButton::getId() const
{
  return this->id;
}
