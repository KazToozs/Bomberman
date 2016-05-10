//
// Keybind.hh for bombi in /Users/pallua_j/rendu/CPP/cpp_indie_studio/sources/Player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Tue May 10 10:27:51 2016 Jules Palluau
// Last update Tue May 10 11:23:22 2016 Jules Palluau
//

#ifndef _KEYBIND_HH_
# define _KEYBIND_HH_

#include "IPlayer.hh"
#include <map>
#include <string>

class Keybind
{
private:
  std::map<int, e_action>  bind1;
  std::map<int, e_action>  bind2;
public:
  Keybind();
  Keybind(const Keybind &);
  ~Keybind();
  const Keybind &operator=(const Keybind &);
  void  init(const std::string &);
  void  override();
  const e_action  &get_action(const int &, const int &);
};

#endif /*!_KEYBIND_HH_*/
