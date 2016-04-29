//
// IAButton.hh for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 15:43:04 2016 maxime liege
// Last update Thu Apr 28 18:35:35 2016 maxime liege
//

#ifndef IABUTTON_H_
#define IABUTTON_H_

#include "Menu.hh"
#include "IButtons.hh"

class IAButton : public IButtons
{

 public:
  IAButton(const NB_IA &id, const std::string &name, Menu *menu);
  virtual ~IAButton();

  virtual void		action() const = 0;
  virtual std::string	getName() const = 0;
  virtual bool		getActive() const = 0;

  const NB_IA		getId() const;

  typedef enum NB_IA
  {
    IA_1 = 1,
    IA_2 = 2,
    IA_3 = 3
  };
  
private:
  const NB_IA		id;
  const std::string	name;
  bool			isActive;
  Menu			*menu;
};

#endif /* !IABUTTON_H_ */
