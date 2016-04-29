//
// ConfirmButton.cpp for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 18:29:22 2016 maxime liege
// Last update Thu Apr 28 18:32:29 2016 maxime liege
//

#include "ConfirmButton.hh"

ConfirmButton::ConfirmButton(const std::string &name, const TYPE_BUTTON type, Menu *menu)
  : name(name), type(type)
{
  this->menu = menu;
}

ConfirmButton::~ConfirmButton()
{

}

void			ConfirmButton::action() const
{

}

const std::string	ConfirmButton::getName() const
{
  return this->name;
}

bool			ConfirmButton::getActive() const
{
  return this->isActive;
}
