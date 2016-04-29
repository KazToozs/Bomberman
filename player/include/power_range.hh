//
// power_range.hh for bombi in /home/palluaj/rendu/CPP/player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 12:59:45 2016 Jules Palluau
// Last update Fri Apr 29 14:16:31 2016 Jules Palluau
//

#ifndef _POWER_RANGE_HH_
# define _POWER_RANGE_HH_

#include "Ipowerup.hh"

class PowerRange: public IPowerup
{
public:
  PowerRange();
  virtual ~PowerRange();
  void set_powerup(IPlayer *) const;
  void unset_powerup(IPlayer *) const;
  e_powerup get_type() const;
};

#endif /*!_POWER_RANGE_HH_*/
