//
// Keybind.hh for bombi in /Users/pallua_j/rendu/CPP/cpp_indie_studio/sources/Player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Tue May 10 10:27:51 2016 Jules Palluau
// Last update Wed May 18 13:02:24 2016 maxime liege
//

#ifndef _KEYBIND_HH_
# define _KEYBIND_HH_

#include "IPlayer.hh"
#include <map>
#include <chrono>
#include <string>

class Gui;

class Keybind
{
private:
  std::chrono::high_resolution_clock::time_point t1;
  std::chrono::high_resolution_clock::time_point t2;
  std::map<int, e_action>  bind1;
  std::map<int, e_action>  bind2;
  Gui                      *_key;

  typedef struct s_keys
  {
    e_action	 key;
    std::string	 cmd;
  }		 t_keys;

  t_keys	keys_tab[6] =
    {
      {UP, "MOVE_UP"},
      {LEFT, "MOVE_LEFT"},
      {DOWN, "MOVE_DOWN"},
      {RIGHT, "MOVE_RIGHT"},
      {BOMB, "BOMB"},
      {UNKNOWN, "0"}
    };

  void parseKey(std::string &str, const int &player);
public:
  Keybind(Gui *);
  Keybind(const Keybind &);
  ~Keybind();
  const Keybind &operator=(const Keybind &);
  void  init(const std::string &);
  void  override();
  e_action  get_action(const int &);
};

#endif /*!_KEYBIND_HH_*/
