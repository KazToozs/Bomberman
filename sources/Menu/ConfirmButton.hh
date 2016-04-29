//
// ConfirmButton.hh for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 18:26:02 2016 maxime liege
// Last update Thu Apr 28 18:32:39 2016 maxime liege
//

#ifndef CONFIRMBUTTON_H_
#define CONFIRMBUTTON_H_

#include "IButtons.hh"
#include "Menu.hh"

class ConfirmButton : public IButtons
{

public:
  ConfirmButton(const std::string &name, const TYPE_BUTTON type, Menu *menu);
  ~ConfirmButton();

  virtual void			action() const;
  virtual const std::string	getName() const;
  virtual bool			getActive() const;

  typedef enum TYPE_BUTTON
    {
      YES = 0,
      NO = 1
    };

private:
  TYPE_BUTTON		type;
  bool			isActive;
  const std::stringx	name;
  Menu			*menu;
};

#endif /* !CONFIRMBUTTON_H_ */
