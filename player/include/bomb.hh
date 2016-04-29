//
// bomb.hh for bombi in /home/palluaj/rendu/CPP/player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Fri Apr 29 15:20:13 2016 Jules Palluau
// Last update Fri Apr 29 17:02:22 2016 Jules Palluau
//

#ifndef _BOMB_HH_
# define _BOMB_HH_

#include <chrono>
#include "Iplayer.hh"



class Map;

class Bomb
{
  private:
    std::chrono::high_resolution_clock::time_point  t;
    t_pos                                           pos;
    int                                             range;
    int                                             team;
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
