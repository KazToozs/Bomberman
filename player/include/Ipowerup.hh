//
// powerup.hh for bombi in /home/palluaj/rendu/CPP/player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Thu Apr 28 16:23:39 2016 Jules Palluau
// Last update Fri Apr 29 17:03:57 2016 Jules Palluau
//

#ifndef _POWERUP_HH_
# define _POWERUP_HH_

#include "Iplayer.hh"

typedef enum powerup
{
  SPEEDUP,
  RANGEUP,
  BOMBUP
}e_powerup;

class IPowerup
{
public:
  IPowerup() {};
  virtual ~IPowerup() {};
  virtual void set_powerup(IPlayer *) const = 0;
  virtual void unset_powerup(IPlayer *) const = 0;
  virtual e_powerup get_type() const = 0;
};

#endif /*!_POWERUP_HH_*/
