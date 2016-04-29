//
// OptionButton.cpp for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 14:12:29 2016 maxime liege
// Last update Thu Apr 28 15:36:50 2016 maxime liege
//

#include "OptionButton.hh"

OptionButton::OptionButton(Menu *menu)
  : name("Option")
{
  this->menu = menu;
}

OptionButton::~OptionButton()
{

}

void		OptionButton::action() const
{

}

std::string	OptionButton::getName() const
{
  return this->name;
}

bool		OptionButton::getActive() const
{
  return this->isActive;
}
