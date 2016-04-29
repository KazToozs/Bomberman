//
// IAButton.cpp for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 15:42:47 2016 maxime liege
// Last update Fri Apr 29 17:01:29 2016 maxime liege
//

#include "IAButton.hh"

IAButton::IAButton(const std::string &name, const NB_IA &id, Menu *menu)
  : id(id), name(name)
{
  this->menu = menu;
}

IAButton::~IAButton()
{  
}

void			IAButton::action() const
{
  
}

const std::string	&IAButton::getName() const
{
  return this->name;
}

bool			IAButton::getActive() const
{
  return this->isActive;
}

IAButton::NB_IA		IAButton::getId() const
{
  return this->id;
}
