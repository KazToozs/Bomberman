//
// player.hh for bombi in /home/palluaj/rendu/CPP/player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Thu Apr 28 14:07:45 2016 Jules Palluau
// Last update Wed May 11 15:00:41 2016 pallua_j
//

#ifndef _PLAYER_HH_
# define _PLAYER_HH_

#include "IPlayer.hh"
#include "Bomb.hh"
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <map>

class Map;
class Gui;
class Keybind;
class Game;

class Player: public IPlayer
{
  typedef void (Player::*ptr)();
private:
  Game                                            *gm;
  std::map<e_action, ptr>                         act_func;
  Keybind                                         *key;
  std::chrono::high_resolution_clock::time_point  t;
  Map                                             *map;
  int                                             team;
  size_t                                          score;
  t_pos                                           pos;
  IPowerup                                        *p;
  size_t                                          max_bombs;
  int                                             range_bomb;
  float                                           speed;
  bool                                            alive;
  std::vector<Bomb *>                             bombs;
  e_action                                        action;
  void  put_bomb();
  void move_up();
  void move_down();
  void move_left();
  void move_right();
public:
  Player(Map *, const int &num, Keybind *, Game *);
  Player(const Player &);
  ~Player();
  void  init();
  const Player &operator=(const Player &);
  e_player get_type() const;
  const e_action &get_action() const;
  void  do_action();
  const std::vector<Bomb *> &get_bombs() const;
  void  check_bombs();
  void  set_pos(const t_pos &);
  const t_pos &get_pos() const;
  bool  is_alive() const;
  bool  check_alive();
  void  check_power_map();
  void set_score(const size_t &);
  void set_maxbombs(const size_t &);
  void set_rangebomb(const int &);
  void  set_speed(const float &);
  void  check_powerup();
  const float &get_speed() const;
  const size_t  &get_score() const;
  void  set_powerups(IPowerup *);
  const int &get_team() const;
};

#endif /*!_PLAYER_HH_*/
