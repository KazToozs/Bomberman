//
// Menu.hh for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
//
// Made by maxime liege
// Login   <liege_m@epitech.net>
//
// Started on  Thu Apr 28 14:12:53 2016 maxime liege
// Last update Wed May 18 14:11:57 2016 maxime liege
//

#ifndef MENU_H_
#define MENU_H_

#include "IButtons.hh"
#include "Gui.hh"

#include <mutex>
#include <vector>

class Menu {
 public:
  Menu(Gui *gui);
  ~Menu();

  void clearList();
  void affList();
  void pushBackList(IButtons *button);
  void GoUp();
  void GoDown();
  void Action();
  void StartGame();
  enum ID_MENU {
    MAIN_MENU = 0,
    OPTIONS = 1,
    PAUSE = 2,
    SOLO_MULTI = 3,
    GAME = 4
  };
  const ID_MENU getId() const;
  const IButtons *getCurrentButton() const;
  const std::string getButtonName() const;
  void CreateMultiPlayer();
  void Unlock() {
      _Mtx->unlock();
  }
  
 private:
  std::mutex* _Mtx;
  std::vector<IButtons *> buttons;
  ID_MENU id_menu;
  int _pos;
  Gui *gui;

  void createMainMenu();
};

typedef void (Menu::*Func_Ptr)(void);

#endif /* !MENU_H_ */
