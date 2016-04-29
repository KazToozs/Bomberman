//
// Menu.hh for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 14:12:53 2016 maxime liege
// Last update Thu Apr 28 18:23:08 2016 maxime liege
//

#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include "IButtons.hh"
#include "Exit.hh"
#include "SoloButton.hh"
#include "MultiButton.hh"
#include "OptionButton.hh"
#include "ContinueButton.hh"

class Menu
{

public:
  Menu();
  ~Menu();

  void	        clearList();
  void		pushBackList(IButtons *button);
  
  typedef enum ID_MENU
    {
      MAIN_MENU = 0,
      OPTIONS = 1,
      PAUSE = 2,
      SOLO_MULTI = 3
    };
private:
  std::vector<IButtons *> buttons;
  ID_MENU		id_menu;

  void			createMainMenu();
};

#endif /* !MENU_H_ */
