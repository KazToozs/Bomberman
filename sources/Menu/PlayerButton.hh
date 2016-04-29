//
// SoloButton.hh for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
// 
// Made by maxime liege
// Login   <liege_m@epitech.net>
// 
// Started on  Thu Apr 28 14:12:46 2016 maxime liege
// Last update Thu Apr 28 17:19:44 2016 maxime liege
//

#ifnde PLAYERBUTTON_H_
#define PLAYERBUTTON_H_

#include "IButtons.hh"
#include "Menu.hh"

class PlayerButton : public IButtons
{

public:
  PlayerButton(const std::string &name, const MODE_PLAYER &id, Menu *menu);
  virtual ~PlayerButton();

  virtual void			action() const;
  virtual const std::string	getName() const;
  virtual bool			getActive() const;

  const short			getId() const;

  typedef enum		MODE_PLAYER
    {
      SOLO = 0,
      MULTI = 1
    };

private:
  const MODE_PLAYER    	id;
  const std::string	name;
  bool			isActive;
  Menu			*menu;
};

#endif /* !PLAYERBUTTON_H_ */
