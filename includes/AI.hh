#ifndef AI_H_
#define AI_H_

#include <map>
#include "IPlayer.hh"
#include "Bomb.hh"
#include "Case.h"
extern "C" {
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}
#include "LuaBridge.h"

class Keybinds;

class AI : public IPlayer
{
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
  Keybinds                                        *key;
  std::vector<Bomb *>                             bombs;
  e_action                                        act;

  typedef void                  (AI::*act_func)();
  std::map<e_action, act_func>  acts;

 public:
   AI(Map *, const int &num);
   AI(const AI &);
   AI &operator=(const AI &);
   ~AI();

   void                       init();
   void                       check_bombs();
   bool                       check_alive();
   void                       check_powerup();

   bool                       is_alive() const;
   e_player                   get_type() const;
   const std::vector<Bomb *> &get_bombs() const;
   const t_pos &              get_pos() const;
   const float &              get_speed() const;
   const e_action &           get_action() const;
   const size_t &             get_score() const;

   void                       set_pos(const t_pos &);
   void                       set_speed(const float &);
   void                       set_score(const size_t &);
   void                       set_maxbombs(const size_t &);
   void                       set_rangebomb(const int &);
   void                       set_powerups(IPowerup *);

   void                       do_action();

private:
   void                       put_bomb();
   void                       move_up();
   void                       move_down();
   void                       move_left();
   void                       move_right();

   void                       pass_values(lua_State *, std::vector<std::vector<Case>>&);
};

#endif /* !AI_H_ */
