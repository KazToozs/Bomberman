//
// power_bomb.cpp for bombi in /home/palluaj/rendu/CPP/player/src/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 13:18:27 2016 Jules Palluau
// Last update Fri Apr 29 17:03:34 2016 Jules Palluau
//

#include "../include/power_bomb.hh"

PowerBomb::PowerBomb()
{

}

PowerBomb::~PowerBomb()
{

}

void  PowerBomb::set_powerup(IPlayer *pl) const
{
  pl->set_maxbombs(1);
}

void  PowerBomb::unset_powerup(IPlayer *pl) const
{
  pl->set_maxbombs(-1);
}

e_powerup PowerBomb::get_type() const
{
  return (BOMBUP);
}
