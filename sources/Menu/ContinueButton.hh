//
// ContinueButton.hh for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 14:20:57 2016 maxime liege
// Last update Fri Apr 29 17:00:25 2016 maxime liege
//

#ifndef CONTINUEBUTTON_H_
#define CONTINUEBUTTON_H_

#include "Menu.hh"

#include <string>

class ContinueButton : public IButtons
{

public:
  ContinueButton(Menu *menu);
  virtual ~ContinueButton();

  virtual void			action() const;
  virtual const std::string	&getName() const;
  virtual bool			getActive() const;

private:
  const std::string	name;
  bool			isActive;
  Menu			*menu;
};

#endif /* !CONTINUEBUTTON_H_ */
