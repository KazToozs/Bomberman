//
// IAButton.hh for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 15:43:04 2016 maxime liege
// Last update Fri Apr 29 17:01:22 2016 maxime liege
//

#ifndef IABUTTON_H_
#define IABUTTON_H_

#include "Menu.hh"

class IAButton : public IButtons
{

 public:
  enum NB_IA
  {
    IA_1 = 1,
    IA_2 = 2,
    IA_3 = 3
  };

  IAButton(const std::string &name, const NB_IA &id, Menu *menu);
  virtual ~IAButton();

  virtual void			action() const;
  virtual const std::string	&getName() const;
  virtual bool			getActive() const;

  NB_IA		getId() const;
  
private:
  const NB_IA		id;
  const std::string	name;
  bool			isActive;
  Menu			*menu;
};

#endif /* !IABUTTON_H_ */
