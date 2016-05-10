//
// Keybind.cpp for bombi in /Users/pallua_j/rendu/CPP/cpp_indie_studio/sources/Player/src/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Tue May 10 10:32:14 2016 Jules Palluau
// Last update Tue May 10 10:38:31 2016 Jules Palluau
//

#include "../include/Keybind.hh"

Keybind::Keybind()
{
  
}

Keybind::Keybind(const Keybind &key)
{
  this->bind = key.bind;
}

Keybind::~Keybind()
{

}

const Keybind   &Keybind::operator=(const Keybind &key)
{
  this->bind = key.bind;
  return (*this);
}

void  Keybind::init(const std::string &file)
{

}
