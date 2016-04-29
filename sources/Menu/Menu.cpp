//
// Menu.cpp for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 14:12:56 2016 maxime liege
// Last update Thu Apr 28 18:23:53 2016 maxime liege
//

#include "Menu.hh"

Menu::Menu()
{
  this->id_menu = MAIN_MENU;
  createMainMenu();
}

Menu::~Menu()
{

}

void	Menu::clearList();
{
  std::vector<IButtons *>::iterator it;
  
  it = buttons.begin();
  while (it != buttons.end())
    {
      delete(*it);
      it++;
    }
  this->buttons.clear();
}

void	Menu::pushBackList(IButtons *button)
{
  this->buttons.push_back(button);
}

void	Menu::createMainMenu()
{
  this->buttons.push_back(new ContinueButton(this));
  this->buttons.push_back(new PlayerButton("Solo", PlayerButton::SOLO, this));
  this->buttons.push_back(new PlayerButton("Multi", PlayerButton::MULTI, this));
  this->buttons.push_back(new OptionButton(this));
  this->buttons.push_back(new ExitButton(this));
}
