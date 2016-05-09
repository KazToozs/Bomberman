//
// bomb.cpp for bombi in /home/palluaj/rendu/CPP/player/src/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 15:29:20 2016 Jules Palluau
// Last update Mon May  9 12:03:20 2016 Jules Palluau
//

#include "../include/Bomb.hh"
#include "../../Map/Map.hh"

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
  std::vector<std::vector<Case> > &mp = m->getMap();

  mp[(int)this->pos.y][(int)this->pos.x]._state = Case::BOMB;
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
  std::vector<std::vector<Case> > &mp = m->getMap();
  bool                            breaked;

  breaked = false;
  if ((std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count()
  - std::chrono::time_point_cast<std::chrono::seconds>(this->t).time_since_epoch().count()) >= 3)
  {
    mp[(int)this->pos.y][(int)this->pos.x]._state = Case::EXPLODING;
    for (int x = 0; x <= this->range && breaked == false; x++)
    {
      if (((int)this->pos.x + x) < mp.size() && mp[(int)this->pos.y][(int)this->pos.x + x]._state != Case::UNBREAKABLE)
      {
        if (mp[(int)this->pos.y][(int)this->pos.x + x]._state == Case::BREAKABLE)
          breaked = true;
        mp[(int)this->pos.y][(int)this->pos.x + x]._state = Case::EXPLODING;
      }
    }
    breaked = false;
    for (int x = 0; x <= this->range && breaked == false; x++)
    {
      if (((int)this->pos.x - x) >= 0 && mp[(int)this->pos.y][(int)this->pos.x - x]._state != Case::UNBREAKABLE)
      {
        if (mp[(int)this->pos.y][(int)this->pos.x - x]._state == Case::BREAKABLE)
          breaked = true;
        mp[(int)this->pos.y][(int)this->pos.x - x]._state = Case::EXPLODING;
      }
    }
    breaked = false;
    for (int y = 0; y <= this->range && breaked == false; y++)
    {
      if (((int)this->pos.y + y) < mp.size() && mp[(int)this->pos.y + y][(int)this->pos.x]._state != Case::UNBREAKABLE)
      {
        if (mp[(int)this->pos.y + y][(int)this->pos.x]._state == Case::BREAKABLE)
          breaked = true;
        mp[(int)this->pos.y + y][(int)this->pos.x]._state = Case::EXPLODING;
      }
    }
    breaked = false;
    for (int y = 0; y <= this->range && breaked == false; y++)
    {
      if (((int)this->pos.y - y) >= 0 && mp[(int)this->pos.y - y][(int)this->pos.x]._state != Case::UNBREAKABLE)
      {
        if (mp[(int)this->pos.y - y][(int)this->pos.x]._state == Case::BREAKABLE)
          breaked = true;
        mp[(int)this->pos.y - y][(int)this->pos.x]._state = Case::EXPLODING;
      }
    }
    return (true);
  }
  return (false);
}
