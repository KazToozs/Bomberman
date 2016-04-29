//
// power_range.cpp for bombi in /home/palluaj/rendu/CPP/player/src/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 13:03:38 2016 Jules Palluau
// Last update Fri Apr 29 17:03:27 2016 Jules Palluau
//

#include "../include/power_range.hh"

PowerRange::PowerRange()
{

}

PowerRange::~PowerRange()
{

}

void  PowerRange::set_powerup(IPlayer *pl) const
{
  pl->set_rangebomb(2);
}

void  PowerRange::unset_powerup(IPlayer *pl) const
{
  pl->set_rangebomb(-2);
}

e_powerup   PowerRange::get_type() const
{
  return (RANGEUP);
}
