//
// IButtons.hh for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 14:13:01 2016 maxime liege
// Last update Fri Apr 29 16:59:54 2016 maxime liege
//

#ifndef IBUTTONS_H_
#define IBUTTONS_H_

#include <string>

class Menu;
typedef void (Menu::*Func_Ptr)(void);

class IButtons
{
 public:
  virtual ~IButtons() {};
  virtual Func_Ptr			action() const = 0;
  virtual const std::string	&getName() const = 0;
  virtual bool			getActive() const = 0;
};

#endif /* !IBUTTONS_H_ */
