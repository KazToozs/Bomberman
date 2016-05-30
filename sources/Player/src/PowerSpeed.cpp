//
// power_speed.cpp for bombi in /home/palluaj/rendu/CPP/player/src/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 14:23:05 2016 Jules Palluau
// Last update Wed May  4 11:52:11 2016 Matheo MSA
//

#include "PowerSpeed.hh"

PowerSpeed::PowerSpeed()
{

}

PowerSpeed::~PowerSpeed()
{

}

void  PowerSpeed::set_powerup(IPlayer *pl) const
{
  pl->set_speed(0.01);
}

void  PowerSpeed::unset_powerup(IPlayer *pl) const
{
  pl->set_speed(-0.01);
}

e_powerup PowerSpeed::get_type() const
{
  return (SPEEDUP);
}
