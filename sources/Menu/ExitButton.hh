//
// ExitButton.hh for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 18:02:38 2016 maxime liege
// Last update Thu Apr 28 18:06:23 2016 maxime liege
//

#ifndef EXITBUTTON_H_
#define EXITBUTTON_H_

#include "IButtons.hh"
#include "Menu.hh"

class ExitButton : public IButtons
{

 public:
   ExitButton(Menu *menu);
   ExitButton(const ExitButton &);
   ExitButton &operator=(const ExitButton &);
   ~ExitButton();

  virtual void			action() const;
  virtual const std::string	getName() const;
  virtual bool			getActive() const;

private:
  const std::string	name;
  bool			isActive;
  Menu			*menu;
};

#endif /* !EXITBUTTON_H_ */
