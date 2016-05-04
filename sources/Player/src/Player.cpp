//
// player.cpp for bombi in /home/palluaj/rendu/CPP/player/src/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 10:32:01 2016 Jules Palluau
// Last update Wed May  4 12:09:47 2016 Jules Palluau
//

#include "../include/Player.hh"
#include "../include/IPowerup.hh"

Player::Player(std::mutex *mutx, Map *mp, const int &num)
{
  this->mtx = mutx;
  this->map = mp;
  this->team = num;
  this->score = 0;
  this->p = NULL;
  this->max_bombs = 1;
  this->range_bomb = 3;
  this->speed = 0.1;
  this->alive = true;
  this->action = UNKNOWN;
}

Player::Player(const Player &pl)
{
  this->map = pl.map;
  this->team = pl.team;
  this->score = pl.score;
  this->pos = pl.pos;
  this->p = pl.p;
  this->max_bombs = pl.max_bombs;
  this->range_bomb = pl.range_bomb;
  this->alive = pl.alive;
  this->key = pl.key;
  this->bombs = pl.bombs;
  this->mtx = pl.mtx;
  this->action = pl.action;
}

Player::~Player()
{
}

const Player  &Player::operator=(const Player &pl)
{
  this->map = pl.map;
  this->team = pl.team;
  this->score = pl.score;
  this->pos = pl.pos;
  this->p = pl.p;
  this->max_bombs = pl.max_bombs;
  this->range_bomb = pl.range_bomb;
  this->alive = pl.alive;
  this->key = pl.key;
  this->bombs = pl.bombs;
  this->mtx = pl.mtx;
  this->action = pl.action;
  return (*this);
}

void  Player::init()
{
  //TODO positionnement dans la map
  //TODO keybinding
}

e_player Player::get_type() const
{
  return (REAL);
}

const e_action &Player::get_action() const
{
  return (this->action);
}

const std::vector<Bomb *> &Player::get_bombs() const
{
  return (this->bombs);
}

void  Player::check_bombs()
{
  for (size_t x = 0; x < this->bombs.size(); x++)
  {
    if (this->bombs[x]->check_bomb(this->map) == true)
      this->bombs.erase(this->bombs.begin() + x);
  }
}

void  Player::put_bomb()
{
  if (this->bombs.size() < this->max_bombs)
  {
    this->bombs.push_back(new Bomb(this->pos, this->range_bomb, this->team));
    this->bombs.back()->put_bomb(this->map);
  }
}

void  Player::set_pos(const t_pos &ps)
{
  this->pos = ps;
}

const t_pos &Player::get_pos() const
{
  return (this->pos);
}

bool  Player::is_alive() const
{
  return (this->alive);
}

bool  Player::check_alive()
{
  //TODO check life
  return (true);
}

void  Player::set_score(const size_t &scr)
{
  this->score += scr;
}

void  Player::set_maxbombs(const size_t &max)
{
  this->max_bombs += max;
}

void  Player::set_rangebomb(const int &range)
{
  this->range_bomb += range;
}

void  Player::set_speed(const float &spd)
{
  this->speed += spd;
}

const float &Player::get_speed() const
{
  return (this->speed);
}

void  Player::set_action(const e_action &act)
{
  //TODO with keybind
}

const size_t &  Player::get_score() const
{
  return (this->score);
}

void  Player::set_powerups(IPowerup *power)
{
  if (power->get_type() == SPEEDUP)
  {
    this->p = power;
    this->t = std::chrono::high_resolution_clock::now();
  }
  power->set_powerup(this);
}

void  Player::check_powerup()
{
  if (this->p != NULL && (std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count()
  - std::chrono::time_point_cast<std::chrono::seconds>(this->t).time_since_epoch().count()) >= 5)
  {
    this->p->unset_powerup(this);
    delete this->p;
    this->p = NULL;
  }
}

void  Player::lock() const
{
  this->mtx->lock();
}

void  Player::unlock() const
{
  this->mtx->unlock();
}
