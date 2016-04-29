//
// ExitButton.cpp for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 18:02:42 2016 maxime liege
// Last update Fri Apr 29 17:01:10 2016 maxime liege
//

#include "ExitButton.hh"

#include "ConfirmButton.hh"

ExitButton::ExitButton(Menu *menu)
  : name("Exit")
{
  this->menu = menu;
}

ExitButton::~ExitButton()
{

}

void			ExitButton::action() const
{
  this->menu->clearList();
  this->menu->pushBackList(new ConfirmButton("Yes", ConfirmButton::YES, this->menu));
  this->menu->pushBackList(new ConfirmButton("No", ConfirmButton::NO, this->menu));
}

const std::string	&ExitButton::getName() const
{
  return this->name;
}

bool			ExitButton::getActive() const
{
  return this->isActive;
}
