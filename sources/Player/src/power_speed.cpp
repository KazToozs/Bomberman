//
// power_speed.cpp for bombi in /home/palluaj/rendu/CPP/player/src/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 14:23:05 2016 Jules Palluau
// Last update Fri Apr 29 17:03:39 2016 Jules Palluau
//

#include "../include/power_speed.hh"

PowerSpeed::PowerSpeed()
{

}

PowerSpeed::~PowerSpeed()
{

}

void  PowerSpeed::set_powerup(IPlayer *pl) const
{
  pl->set_speed(0.1);
}

void  PowerSpeed::unset_powerup(IPlayer *pl) const
{
  pl->set_speed(-0.1);
}

e_powerup PowerSpeed::get_type() const
{
  return (SPEEDUP);
}
