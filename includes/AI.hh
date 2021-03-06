#ifndef AI_H_
#define AI_H_

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(lib, "lua.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include <map>
#include <chrono>
#include "IPlayer.hh"
#include "Bomb.hh"
#include "Case.h"
extern "C" {
# include <lua/lua.h>
# include <lua/lauxlib.h>
# include <lua/lualib.h>
}
#include "LuaBridge/LuaBridge.h"

class Keybinds;
class Game;

class AI : public IPlayer
{
  std::chrono::high_resolution_clock::time_point  t;
  Game                                            *gm;
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

  #ifdef _WIN32
  std::string path_script = ".\\Ressources\\Script\\";
  #else
  std::string path_script = "./Ressources/Script/";
  #endif // _WIN32


  typedef void                  (AI::*act_func)();
  std::map<e_action, act_func>  acts;

 public:
   AI(Map *, const int &num, Game *);
   AI(const AI &);
   AI &operator=(const AI &);
   ~AI();

   void                       init();
   void                       check_bombs();
   bool                       check_alive();
   void                       check_powerup();
   void                       check_power_map();

   bool                       is_alive() const;
   e_player                   get_type() const;
   const int                  &get_team() const;
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

   void                       setLuaPath(lua_State *L, const char *path) const;
   void                       pass_values(lua_State *, std::vector<std::vector<Case>> const &) const;
};

#endif /* !AI_H_ */
