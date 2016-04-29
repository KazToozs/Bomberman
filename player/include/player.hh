//
// player.hh for bombi in /home/palluaj/rendu/CPP/player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Thu Apr 28 14:07:45 2016 Jules Palluau
// Last update Fri Apr 29 16:45:26 2016 Jules Palluau
//

#ifndef _PLAYER_HH_
# define _PLAYER_HH_

#include <thread>
#include "Iplayer.hh"
#include "bomb.hh"
#include <mutex>
#include <condition_variable>
#include <chrono>

class Map;
class Keybinds;

class Player: public IPlayer
{
private:
  std::chrono::high_resolution_clock::time_point  t;
  std::thread                                     *th;
  Map                                             *map;
  int                                             team;
  size_t                                          score;
  t_pos                                           pos;
  IPowerup                                        *p;
  size_t                                          max_bombs;
  int                                             range_bomb;
  float                                           speed;
  bool                                            alive;
  Keybinds                                        *key;
  std::vector<Bomb *>                             bombs;
  std::condition_variable                         *cnd;
  std::mutex                                      *mtx;
  e_action                                        action;
public:
  Player(std::mutex *, std::condition_variable *, Map *, const int &num);
  Player(const Player &);
  virtual ~Player();
  void  start();
  void  init();
  const Player &operator=(const Player &);
  e_player get_type() const;
  const e_action &get_action() const;
  const std::vector<Bomb *> &get_bombs() const;
  void  put_bomb();
  void  set_pos(const t_pos &);
  const t_pos &get_pos() const;
  bool  is_alive() const;
  bool  check_alive();
  void set_score(const size_t &);
  void set_maxbombs(const size_t &);
  void set_rangebomb(const int &);
  void  set_speed(const float &);
  void  check_powerup();
  const float &get_speed() const;
  void set_action(const e_action &);
  const size_t  &get_score() const;
  void  set_powerups(IPowerup *);
  void  wait() const;
  void  lock() const;
  void  unlock() const;
};

#endif /*!_PLAYER_HH_*/
