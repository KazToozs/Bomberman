//
// power_bomb.hh for bombi in /home/palluaj/rendu/CPP/player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 13:16:03 2016 Jules Palluau
// Last update Fri Apr 29 14:15:28 2016 Jules Palluau
//

#ifndef _POWER_BOMB_HH_
# define _POWER_BOMB_HH_

#include "Ipowerup.hh"

class PowerBomb: public IPowerup
{
public:
  PowerBomb();
  ~PowerBomb();
  void set_powerup(IPlayer *) const;
  void unset_powerup(IPlayer *) const;
  e_powerup get_type() const;
};

#endif /*!_POWER_BOMB_HH_*/
