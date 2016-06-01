//
// ConfirmButton.hh for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 18:26:02 2016 maxime liege
// Last update Fri Apr 29 17:00:13 2016 maxime liege
//

#ifndef CONFIRMBUTTON_H_
#define CONFIRMBUTTON_H_

#include "Menu.hh"

class ConfirmButton : public IButtons
{

public:
  enum TYPE_BUTTON
    {
      YES = 0,
      NO = 1
    };

  ConfirmButton(const std::string &name, const TYPE_BUTTON type, Menu *menu);
  ~ConfirmButton();

  virtual Func_Ptr			action() const;
  virtual const std::string	&getName() const;
  virtual bool			getActive() const;

  TYPE_BUTTON			getType();
private:
  const TYPE_BUTTON	_type;
  bool			isActive;
  const std::string	_name;
  Menu			*menu;

};

#endif /* !CONFIRMBUTTON_H_ */
