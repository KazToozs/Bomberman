//
// OptionButton.hh for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 14:12:33 2016 maxime liege
// Last update Thu Apr 28 18:07:10 2016 maxime liege
//

#ifndef OPTIONBUTTON_H_
#define OPTIONBUTTON_H_

#include "IButtons.hh"
#include "Menu.hh"

class OptionButton : public IButtons
{

public:
  OptionButton(Menu *menu);
  ~OptionButton();

  virtual void			action() const;
  virtual const std::string	getName() const;
  virtual bool			getActive() const;

private:
  const std::string	name;
  bool			isActive;
  Menu			*menu;
};

#endif /* !OPTIONBUTTON_H_ */
