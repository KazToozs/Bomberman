//
// Menu.hh for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 14:12:53 2016 maxime liege
// Last update Fri Apr 29 15:35:52 2016 maxime liege
//

#ifndef MENU_H_
#define MENU_H_

#include "IButtons.hh"

#include <vector>

class Menu
{

public:
  Menu();
  ~Menu();

  void	        clearList();
  void		affList();
  void		pushBackList(IButtons *button);
  
  enum ID_MENU
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
