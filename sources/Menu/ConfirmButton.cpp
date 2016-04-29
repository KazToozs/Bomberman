//
// ConfirmButton.cpp for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 18:29:22 2016 maxime liege
// Last update Fri Apr 29 17:02:59 2016 maxime liege
//

#include "ConfirmButton.hh"

ConfirmButton::ConfirmButton(const std::string &name, 
			     const ConfirmButton::TYPE_BUTTON type, Menu *menu)
  : _type(type),  _name(name)
{
  this->menu = menu;
}

ConfirmButton::~ConfirmButton()
{

}

void				ConfirmButton::action() const
{

}

const std::string		&ConfirmButton::getName() const
{
  return this->_name;
}

bool				ConfirmButton::getActive() const
{
  return this->isActive;
}

ConfirmButton::TYPE_BUTTON	ConfirmButton::getType()
{
  return this->_type;
}
