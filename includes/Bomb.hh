//
// bomb.hh for bombi in /home/palluaj/rendu/CPP/player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 15:20:13 2016 Jules Palluau
// Last update Wed May 11 12:48:53 2016 pallua_j
//

#ifndef _BOMB_HH_
# define _BOMB_HH_

#include <chrono>
#include <vector>
#include "IPlayer.hh"
#include "Map.hh"

class Map;

class Bomb
{
  private:
    std::chrono::high_resolution_clock::time_point  t;
    t_pos                                           pos;
    int                                             range;
    int                                             team;
    void                                            do_explosion(std::vector<std::vector<Case> > &) const;
    void                                            del_explosion(std::vector<std::vector<Case> > &) const;
  public:
    Bomb(const t_pos &, const int &, const int &);
    Bomb(const Bomb &);
    ~Bomb();
    const Bomb &operator=(const Bomb &);
    void  put_bomb(Map *);
    const t_pos &get_pos() const;
    const int  &get_team() const;
    bool  check_bomb(Map *);
};

#endif /*!_BOMB_HH_*/
