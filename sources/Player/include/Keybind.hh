//
// Keybind.hh for bombi in /Users/pallua_j/rendu/CPP/cpp_indie_studio/sources/Player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Tue May 10 10:27:51 2016 Jules Palluau
// Last update Tue May 10 10:37:50 2016 Jules Palluau
//

#ifndef _KEYBIND_HH_
# define _KEYBIND_HH_

#include "IPlayer.hh"
#include <map>
#include <string>

class Keybind
{
private:
  std::map<e_action, int>  bind;
public:
  Keybind();
  Keybind(const Keybind &);
  ~Keybind();
  const Keybind &operator=(const Keybind &);
  void  init(const std::string &);
};

#endif /*!_KEYBIND_HH_*/
