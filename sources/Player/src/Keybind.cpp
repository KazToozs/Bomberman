//
// Keybind.cpp for bombi in /Users/pallua_j/rendu/CPP/cpp_indie_studio/sources/Player/src/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Tue May 10 10:32:14 2016 Jules Palluau
// Last update Tue May 10 11:23:36 2016 Jules Palluau
//

#include "../include/Keybind.hh"

Keybind::Keybind()
{
  bind1[0x5A] = UP;
  bind1[0x53] = DOWN;
  bind1[0x51] = LEFT;
  bind1[0x44] = RIGHT;
  bind1[0x20] = BOMB;

  bind2[0x26] = UP;
  bind2[0x28] = DOWN;
  bind2[0x25] = LEFT;
  bind2[0x27] = RIGHT;
  bind2[0xA1] = BOMB;
}

Keybind::Keybind(const Keybind &key)
{
  this->bind1 = key.bind1;
  this->bind2 = key.bind2;
}

Keybind::~Keybind()
{

}

const Keybind   &Keybind::operator=(const Keybind &key)
{
  this->bind2 = key.bind2;
  this->bind1 = key.bind1;
  return (*this);
}

void  Keybind::init(const std::string &file)
{
  //TODO Liege
}

void  Keybind::override()
{
  //TODO Liege
}

const e_action  &Keybind::get_action(const int &key, const int &player)
{
  if (player == 1)
    return (this->bind1[key]);
  else
    return (this->bind2[key]);
}
