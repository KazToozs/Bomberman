//
// IAButton.cpp for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 15:42:47 2016 maxime liege
// Last update Thu Apr 28 18:35:18 2016 maxime liege
//

#include "IAButton.hh"

IAButton::IAButton(const NB_IA &id, const std::string &name, Menu *menu)
  : id(id), name(name)
{
}

IAButton::~IAButton()
{  
}

void		IAButton::action() const
{
  
}

std::string	IAButton::getName() const
{
  return this->name;
}

bool		IAButton::getActive() const
{
  return this->isActive;
}

const bool	IAButton::getId() const
{
  return this->id;
}
