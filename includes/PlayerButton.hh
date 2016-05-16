//
// SoloButton.hh for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 14:12:46 2016 maxime liege
// Last update Fri Apr 29 16:59:32 2016 maxime liege
//

#ifndef PLAYERBUTTON_H_
#define PLAYERBUTTON_H_

#include "Menu.hh"

#include <string>

class PlayerButton : public IButtons
{

public:
  enum		MODE_PLAYER
    {
      SOLO = 0,
      MULTI = 1
    };

  PlayerButton(const std::string &name, const MODE_PLAYER &id, Menu *menu);
  virtual ~PlayerButton();

  virtual void			action() const;
  virtual const std::string	&getName() const;
  virtual bool			getActive() const;

  MODE_PLAYER		getId() const;

private:
  MODE_PLAYER const	_id;
  std::string const	_name;
  bool			isActive;
  Menu			*menu;
};

#endif /* !PLAYERBUTTON_H_ */
