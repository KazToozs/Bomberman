//
// power_speed.hh for bombi in /home/palluaj/rendu/CPP/player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 14:18:05 2016 Jules Palluau
// Last update Fri Apr 29 14:22:22 2016 Jules Palluau
//

#ifndef _POWER_SPEED_HH_
# define _POWER_SPEED_HH_

#include "Ipowerup.hh"

class PowerSpeed: public IPowerup
{
public:
  PowerSpeed();
  ~PowerSpeed();
  void  set_powerup(IPlayer *) const;
  void  unset_powerup(IPlayer *) const;
  e_powerup get_type() const;
};

#endif /*!_POWER_SPEED_HH_*/
