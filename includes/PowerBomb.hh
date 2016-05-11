//
// power_bomb.hh for bombi in /home/palluaj/rendu/CPP/player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 13:16:03 2016 Jules Palluau
// Last update Wed May  4 11:56:57 2016 Matheo MSA
//

#ifndef _POWER_BOMB_HH_
# define _POWER_BOMB_HH_

#include "IPowerup.hh"

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
