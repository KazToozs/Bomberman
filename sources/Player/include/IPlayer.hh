//
// Iplayer.hh for bombi in /home/palluaj/rendu/CPP/player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Thu Apr 28 13:10:27 2016 Jules Palluau
// Last update Wed May  4 13:42:14 2016 Jules Palluau
//

#ifndef _IPLAYER_HH_
# define _IPLAYER_HH_

#include <unistd.h>
#include <vector>

typedef enum player
{
  AI,
  REAL
}e_player;

typedef enum action
{
  UNKNOWN,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  BOMB
}e_action;

typedef struct s_pos
{
  int   tx;
  int   ty;
  float rx;
  float ry;
}         t_pos;

class Bomb;
class IPowerup;

class IPlayer {
public:
  IPlayer() {};
  virtual ~IPlayer() {};
  virtual void  init() = 0;
  virtual e_player get_type() const = 0;
  virtual const std::vector<Bomb *> &get_bombs() const = 0;
  virtual void check_bombs() = 0;
  virtual void put_bomb() = 0;
  virtual void set_pos(const t_pos &) = 0;
  virtual const t_pos &get_pos() const = 0;
  virtual void  set_speed(const float &) = 0;
  virtual const float &get_speed() const = 0;
  virtual bool  is_alive() const = 0;
  virtual void  check_powerup() = 0;
  virtual bool check_alive() = 0;
  virtual void set_score(const size_t &) = 0;
  virtual void set_maxbombs(const size_t &) = 0;
  virtual void set_rangebomb(const int &) = 0;
  virtual const e_action &get_action() const = 0;
  virtual void do_action() = 0;
  virtual const size_t  &get_score() const = 0;
  virtual void  set_powerups(IPowerup *) = 0;
  virtual void  lock() const = 0;
  virtual void  unlock() const = 0;
};

#endif /*!_IPLAYER_HH_*/
