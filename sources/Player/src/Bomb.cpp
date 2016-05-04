//
// bomb.cpp for bombi in /home/palluaj/rendu/CPP/player/src/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 15:29:20 2016 Jules Palluau
// Last update Wed May  4 11:51:35 2016 Matheo MSA
//

#include "../include/Bomb.hh"

Bomb::Bomb(const t_pos &p, const int &rng, const int &t)
{
  this->pos = p;
  this->range = rng;
  this->team = t;
  this->t = std::chrono::high_resolution_clock::now();
}

Bomb::Bomb(const Bomb &bmb)
{
  this->pos = bmb.pos;
  this->range = bmb.range;
  this->team = bmb.team;
  this->t = bmb.t;
}

Bomb::~Bomb()
{

}

const Bomb  &Bomb::operator=(const Bomb &bmb)
{
  this->pos = bmb.pos;
  this->range = bmb.range;
  this->team = bmb.team;
  this->t = bmb.t;
  return (*this);
}

void  Bomb::put_bomb(Map *m)
{
  //TODO put bomb on map
}

const t_pos   &Bomb::get_pos() const
{
  return (this->pos);
}

const int   &Bomb::get_team() const
{
  return (this->team);
}

bool  Bomb::check_bomb(Map *m)
{
  if ((std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count()
  - std::chrono::time_point_cast<std::chrono::seconds>(this->t).time_since_epoch().count()) >= 3)
  {
    //TODO explosion
    return (true);
  }
  return (false);
}
