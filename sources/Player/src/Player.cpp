//
// player.cpp for bombi in /home/palluaj/rendu/CPP/player/src/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 10:32:01 2016 Jules Palluau
// Last update Wed May 11 15:05:37 2016 pallua_j
//

#include "Player.hh"
#include "IPowerup.hh"
#include "Map.hh"
#include "Case.h"
#include "Game.hh"
#include "Keybind.hh"
#include "Gui.hh"


Player::Player(Map *mp, const int &num, Keybind *keys, Game *g)
{
  this->gm = g;
  this->key = keys;
  act_func[UP] = &Player::move_down;
  act_func[DOWN] = &Player::move_up;
  act_func[LEFT] = &Player::move_left;
  act_func[RIGHT] = &Player::move_right;
  act_func[BOMB] = &Player::put_bomb;
  this->map = mp;
  this->team = num;
  this->score = 0;
  this->p = NULL;
  this->max_bombs = 1;
  this->range_bomb = 2;
  this->speed = 0.025;
  this->alive = true;
  this->action = UNKNOWN;
  this->pos.x = 0.0;
  this->pos.y = 0.5;
}

Player::Player(const Player &pl)
{
  this->act_func = pl.act_func;
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
  this->action = pl.action;
}

Player::~Player()
{
}

const Player  &Player::operator=(const Player &pl)
{
  this->act_func = pl.act_func;
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
  this->action = pl.action;
  return (*this);
}

void  Player::init()
{
  std::vector<std::vector<Case> > &mp = this->map->getMap();

  if ((this->team % 2) == 0)
    this->pos.x += (mp.size() - 1);
  if (this->team > 2)
    this->pos.y += (mp.size() - 1);
  mp[(int)this->pos.y][(int)this->pos.x]._state = Case::TAKEN;
}

IPlayer::e_player Player::get_type() const
{
  return (IPlayer::REAL);
}

const std::vector<Bomb *> &Player::get_bombs() const
{
  return (this->bombs);
}

void  Player::check_bombs()
{
  for (size_t x = 0; x < this->bombs.size(); x++)
  {
    if (this->bombs[x]->check_bomb(this->map, this->gm) == true)
      this->bombs.erase(this->bombs.begin() + x);
  }
}

void  Player::put_bomb()
{
  std::vector<std::vector<Case> > &mp = this->map->getMap();

  if (this->bombs.size() < this->max_bombs && mp[static_cast<int>(this->pos.y)][static_cast<int>(this->pos.x)]._state != Case::BOMB)
  {
    this->bombs.push_back(new Bomb(this->pos, this->range_bomb, this->team));
    this->bombs.back()->put_bomb(this->map);
    this->gm->set_actualisation(true);
  }
}

const int &Player::get_team() const
{
  return (this->team);
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
  std::vector<std::vector<Case> > &mp = this->map->getMap();

  if (mp[(int)this->pos.y][(int)this->pos.x]._state == Case::EXPLODING)
  {
    this->alive = false;
    return (false);
  }
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

const e_action  &Player::get_action() const
{
  return (this->action);
}

void  Player::move_up()
{
  std::vector<std::vector<Case> > &mp = this->map->getMap();
  float   tmp;

  if ((this->pos.y - this->speed) >= 0.1)
  {
    tmp = this->pos.y - this->speed;
    if (static_cast<int>(this->pos.y) != static_cast<int>(tmp))
      {
        if (mp[static_cast<int>(tmp)][this->pos.x]._state == Case::FREE)
        {
            if (mp[static_cast<int>(this->pos.y)][static_cast<int>(this->pos.x)]._state == Case::BOMB)
            {
                mp[static_cast<int>(tmp)][this->pos.x]._state = Case::TAKEN;
              this->pos.y = tmp;
            }
            else
            {
                mp[static_cast<int>(this->pos.y)][this->pos.x]._state = Case::FREE;
                this->pos.y = tmp;
                mp[static_cast<int>(this->pos.y)][this->pos.x]._state = Case::TAKEN;
            }
        }
        else if (mp[static_cast<int>(tmp)][this->pos.x]._state == Case::EXPLODING)
        {
            if (mp[static_cast<int>(this->pos.y)][static_cast<int>(this->pos.x)]._state == Case::BOMB)
            {
              this->pos.y = tmp;
            }
            else
            {
                mp[static_cast<int>(this->pos.y)][this->pos.x]._state = Case::FREE;
                this->pos.y = tmp;
            }
        }
      }
    else
      this->pos.y = tmp;
  }
}

void  Player::move_down()
{
  std::vector<std::vector<Case> > &mp = this->map->getMap();
  float   tmp;

  if ((this->pos.y + this->speed) < (mp.size() - 0.1))
  {
    tmp = this->pos.y + this->speed;
    if (static_cast<int>(this->pos.y) != static_cast<int>(tmp))
      {
        if (mp[static_cast<int>(tmp)][this->pos.x]._state == Case::FREE)
        {
            if (mp[static_cast<int>(this->pos.y)][this->pos.x]._state == Case::BOMB)
            {
                mp[static_cast<int>(tmp)][this->pos.x]._state = Case::TAKEN;
              this->pos.y = tmp;
            }
            else
            {
                mp[static_cast<int>(this->pos.y)][this->pos.x]._state = Case::FREE;
                this->pos.y = tmp;
                mp[static_cast<int>(this->pos.y)][this->pos.x]._state = Case::TAKEN;
            }
        }
        else if (mp[static_cast<int>(tmp)][this->pos.x]._state == Case::EXPLODING)
        {
            if (mp[static_cast<int>(this->pos.y)][this->pos.x]._state == Case::BOMB)
            {
              this->pos.y = tmp;
            }
            else
            {
                mp[static_cast<int>(this->pos.y)][this->pos.x]._state = Case::FREE;
                this->pos.y = tmp;
            }
        }
      }
    else
      this->pos.y = tmp;
  }
}

void  Player::move_left()
{
  std::vector<std::vector<Case> > &mp = this->map->getMap();
  float   tmp;

  if ((this->pos.x - this->speed) >= 0.1)
  {
    tmp = this->pos.x - this->speed;
    if (static_cast<int>(this->pos.x) != static_cast<int>(tmp))
      {
        if (mp[this->pos.y][static_cast<int>(tmp)]._state == Case::FREE)
        {
            if (mp[static_cast<int>(this->pos.y)][static_cast<int>(this->pos.x)]._state == Case::BOMB)
            {
                mp[static_cast<int>(this->pos.y)][static_cast<int>(tmp)]._state = Case::TAKEN;
              this->pos.x = tmp;
            }
            else
            {
                mp[this->pos.y][static_cast<int>(this->pos.x)]._state = Case::FREE;
                this->pos.x = tmp;
                mp[this->pos.y][static_cast<int>(this->pos.x)]._state = Case::TAKEN;
            }
        }
        else if (mp[this->pos.y][static_cast<int>(tmp)]._state == Case::EXPLODING)
        {
            if (mp[static_cast<int>(this->pos.y)][static_cast<int>(this->pos.x)]._state == Case::BOMB)
            {
              this->pos.x = tmp;
            }
            else
            {
                mp[this->pos.y][static_cast<int>(this->pos.x)]._state = Case::FREE;
                this->pos.x = tmp;
            }
        }
      }
    else
      this->pos.x = tmp;
  }
}

void  Player::move_right()
{
  std::vector<std::vector<Case> > &mp = this->map->getMap();
  float   tmp;

  if ((this->pos.x + this->speed) < (mp.size() - 0.1))
  {
    tmp = this->pos.x + this->speed;
    if (static_cast<int>(this->pos.x) != static_cast<int>(tmp))
      {
        if (mp[static_cast<int>(this->pos.y)][static_cast<int>(tmp)]._state == Case::FREE)
         {
            if (mp[static_cast<int>(this->pos.y)][static_cast<int>(this->pos.x)]._state == Case::BOMB)
             {
                mp[static_cast<int>(this->pos.y)][static_cast<int>(tmp)]._state = Case::TAKEN;
               this->pos.x = tmp;
             }
            else
            {
                mp[static_cast<int>(this->pos.y)][static_cast<int>(this->pos.x)]._state = Case::FREE;
                this->pos.x = tmp;
                mp[static_cast<int>(this->pos.y)][static_cast<int>(this->pos.x)]._state = Case::TAKEN;
            }
         }
        else if (mp[static_cast<int>(this->pos.y)][static_cast<int>(tmp)]._state == Case::EXPLODING)
         {
            if (mp[static_cast<int>(this->pos.y)][static_cast<int>(this->pos.x)]._state == Case::BOMB)
             {
               this->pos.x = tmp;
             }
            else
            {
                mp[static_cast<int>(this->pos.y)][static_cast<int>(this->pos.x)]._state = Case::FREE;
                this->pos.x = tmp;
            }
         }
      }
    else
      this->pos.x = tmp;
  }
}

void  Player::do_action()
{
   e_action bind;

   bind = UNKNOWN;
   bind = key->get_action(this->team);
   if (bind != UNKNOWN)
     (this->*act_func[bind])();
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

void  Player::check_power_map()
{
    std::vector<std::vector<Case> > &mp = this->map->getMap();

    if (this->p == NULL && mp[static_cast<int>(this->pos.y)][static_cast<int>(this->pos.x)]._powerup != NULL)
    {
        this->set_powerups(mp[static_cast<int>(this->pos.y)][static_cast<int>(this->pos.x)]._powerup);
        mp[static_cast<int>(this->pos.y)][static_cast<int>(this->pos.x)]._powerup = NULL;
            this->gm->set_actualisation(true);
    }
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
