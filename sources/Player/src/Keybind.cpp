//
// Keybind.cpp for bombi in /Users/pallua_j/rendu/CPP/cpp_indie_studio/sources/Player/src/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Tue May 10 10:32:14 2016 Jules Palluau
// Last update Wed May 18 13:02:40 2016 maxime liege
//

#include "Keybind.hh"
#include "Gui.hh"

#include <iostream>
#include <fstream>

Keybind::Keybind(Gui *key)
{
  this->_key = key;
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
  this->_key = key._key;
  this->bind1 = key.bind1;
  this->bind2 = key.bind2;
}

Keybind::~Keybind()
{

}

const Keybind   &Keybind::operator=(const Keybind &key)
{
  this->_key = key._key;
  this->bind2 = key.bind2;
  this->bind1 = key.bind1;
  return (*this);
}

void  Keybind::parseKey(std::string &str, const int &player)
{
  std::string type;
  std::string key;
  int i;
  long int key16;

  i = 0;
  type = str.substr(0, str.find("="));
  key = str.substr(str.find("=") + 1);
  key16 = strtol(key.c_str(), NULL, 16);
  std::cout << type << " " << key16 << std::endl;
  while (type.compare(keys_tab[i].cmd) && keys_tab[i].cmd.compare("0"))
    i++;
  if (keys_tab[i].cmd.compare("0") && !type.compare(keys_tab[i].cmd))
    {
      if (player == 1)
	bind1[strtol(key.c_str(), NULL, 16)] = keys_tab[i].key;
      else
	bind2[strtol(key.c_str(), NULL, 16)] = keys_tab[i].key;
    }
}

void  Keybind::init(const std::string &file)
{
  std::ifstream ifs;
  std::string str;
  int numPlayer;
  
  numPlayer = 0;
  ifs.open (file, std::ifstream::in);
  if (ifs.is_open())
    {
      while (std::getline(ifs, str))
        {
	  if (!str.compare("[P1]"))
	    numPlayer = 1;
	  else if (!str.compare("[P2]"))
	    numPlayer = 2;
	  if (str.compare("") && str.compare("[P1]") 
	      && str.compare("[P2]") && numPlayer != 0)
	    this->parseKey(str, numPlayer);
	}
      ifs.close();
    }
  if (numPlayer == 0)
    std::cout << "No players were found." << std::endl; 
}

void  Keybind::override()
{
  std::ofstream ofs;
  
}

e_action  Keybind::get_action(const int &player)
{
  if (player == 1)
  {
    const std::vector<irr::SEvent::SKeyInput>& keys = _key->get_key_event();

    for (size_t x = 0; x < keys.size(); x++)
    {
       // usleep(200000);
        if (bind1[x])
            std::cout << std::boolalpha << "test: " << bind1[x] << " presse: " << keys[x].PressedDown << std::endl;
        if (bind1[x] != UNKNOWN && keys[x].PressedDown)
            return (bind1[keys[x].Key]);
    }
    return (UNKNOWN);
  }
  else
  {
      const std::vector<irr::SEvent::SKeyInput>& keys = _key->get_key_event();

      for (size_t x = 0; x < keys.size(); x++)
      {
          if (bind2[x] != UNKNOWN && keys[x].PressedDown)
              return (bind2[keys[x].Key]);
      }
      return (UNKNOWN);
  }
}
