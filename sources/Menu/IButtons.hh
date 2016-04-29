//
// IButtons.hh for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 14:13:01 2016 maxime liege
// Last update Thu Apr 28 15:38:53 2016 maxime liege
//

#ifndef IBUTTONS_H_
#define IBUTTONS_H_

class IButtons
{
 public:
  virtual ~IButtons() {};
  virtual void			action() const = 0;
  virtual const std::string	getName() const = 0;
  virtual bool			getActive() const = 0;
};

#endif /* !IBUTTONS_H_ */
