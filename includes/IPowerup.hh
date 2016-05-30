//
// powerup.hh for bombi in /home/palluaj/rendu/CPP/player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Thu Apr 28 16:23:39 2016 Jules Palluau
// Last update Wed May  4 11:57:27 2016 Matheo MSA
//

#ifndef _POWERUP_HH_
# define _POWERUP_HH_

#include "IPlayer.hh"
#include "Case.h"

typedef enum powerup
{
  SPEEDUP = 10,
  RANGEUP = 9,
  BOMBUP = 8
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
