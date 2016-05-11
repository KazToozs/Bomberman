//
// power_speed.hh for bombi in /home/palluaj/rendu/CPP/player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 14:18:05 2016 Jules Palluau
// Last update Wed May  4 11:57:08 2016 Matheo MSA
//

#ifndef _POWER_SPEED_HH_
# define _POWER_SPEED_HH_

#include "IPowerup.hh"

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
