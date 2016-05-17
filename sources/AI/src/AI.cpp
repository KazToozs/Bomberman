#include "AI.hh"
#include "../../Player/include/IPowerup.hh"
#include "Map.hh"
#include "Case.h"
#include <iostream>

AI::AI(Map *mp, const int &num)
{
  this->map = mp;
  this->team = num;
  this->score = 0;
  this->p = NULL;
  this->max_bombs = 1;
  this->range_bomb = 3;
  this->speed = 0.1;
  this->alive = true;
  this->act = UNKNOWN;
  this->pos.x = 0.5;
  this->pos.y = 0.5;

  this->acts[UNKNOWN] = NULL;
  this->acts[UP] = &AI::move_up;
  this->acts[DOWN] = &AI::move_down;
  this->acts[LEFT] = &AI::move_left;
  this->acts[RIGHT] = &AI::move_right;
  this->acts[BOMB] = &AI::put_bomb;
}

AI::AI(const AI &pl)
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
  this->act = pl.act;

  this->acts[UNKNOWN] = NULL;
  this->acts[UP] = &AI::move_up;
  this->acts[DOWN] = &AI::move_down;
  this->acts[LEFT] = &AI::move_left;
  this->acts[RIGHT] = &AI::move_right;
  this->acts[BOMB] = &AI::put_bomb;
}

AI::~AI()
{
}

AI  &AI::operator=(const AI &pl)
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
  this->act = pl.act;
  return (*this);
}

void  AI::init()
{
  std::vector<std::vector<Case> > &mp = this->map->getMap();

  if ((this->team % 2) == 0)
  {
    this->pos.x += (mp.size() - 1);
  }
  if (this->team > 2)
  {
    this->pos.y += (mp.size() - 1);
  }
  mp[this->pos.y][this->pos.x]._state = Case::TAKEN;
  //TODO keybinding
}

IPlayer::e_player AI::get_type() const
{
  return (IPlayer::AI);
}

const std::vector<Bomb *> &AI::get_bombs() const
{
  return (this->bombs);
}

void  AI::check_bombs()
{
  for (size_t x = 0; x < this->bombs.size(); x++)
  {
    if (this->bombs[x]->check_bomb(this->map) == true)
      this->bombs.erase(this->bombs.begin() + x);
  }
}

void  AI::put_bomb()
{
  if (this->bombs.size() < this->max_bombs)
  {
    this->bombs.push_back(new Bomb(this->pos, this->range_bomb, this->team));
    this->bombs.back()->put_bomb(this->map);
  }
}

void  AI::set_pos(const t_pos &ps)
{
  this->pos = ps;
}

const t_pos &AI::get_pos() const
{
  return (this->pos);
}

bool  AI::is_alive() const
{
  return (this->alive);
}

bool  AI::check_alive()
{
  std::vector<std::vector<Case> > &mp = this->map->getMap();

  if (mp[this->pos.y][this->pos.x]._state == Case::EXPLODING)
  {
    this->alive = false;
    return (false);
  }
  return (true);
}

void  AI::set_score(const size_t &scr)
{
  this->score += scr;
}

void  AI::set_maxbombs(const size_t &max)
{
  this->max_bombs += max;
}

void  AI::set_rangebomb(const int &range)
{
  this->range_bomb += range;
}

void  AI::set_speed(const float &spd)
{
  this->speed += spd;
}

const float &AI::get_speed() const
{
  return (this->speed);
}

const e_action  &AI::get_action() const
{
  return (this->act);
}

void                AI::pass_values(lua_State *L, std::vector<std::vector<Case>> &map)
{
  /* Pass map sizes */
  lua_pushnumber(L, map.size());
  lua_setglobal(L, "map_y");
  lua_pushnumber(L, map[0].size());
  lua_setglobal(L, "map_x");

  /* Pass positions */
  lua_pushnumber(L, static_cast<int>(this->pos.x + 1));
  lua_setglobal(L, "pos_x");
  lua_pushnumber(L, static_cast<int>(this->pos.y + 1));
  lua_setglobal(L, "pos_y");

  /* make a table with the map valeus */
  lua_newtable(L);
  int newTable = lua_gettop(L);
  int index = 1;
  for (int y = 0; y < map.size(); y++)
  {
    for (int x = 0; x < map[y].size(); x++)
    {
      lua_pushnumber(L, map[y][x]._state);
      lua_rawseti(L, -2, index);
      ++index;
    }
  }
  lua_setglobal(L, "map");
}

void                                AI::do_action()
{
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);
  int r = luaL_loadfile(L, "luascript.lua");
  pass_values(L, this->map->getMap());
  if (r == 0)
  {
    r = lua_pcall(L, 0, 0, 0);
  }
  luabridge::LuaRef a = luabridge::getGlobal(L, "actionChoice");
  e_action act = static_cast<e_action>(a.cast<int>());
  // std::cout << "action: " << act << std::endl;
  if (act != UNKNOWN)
  {
    (this->*acts[act])();
  }
  // lua_close(L);
  //TODO do an action with what the script returns, then close the luascript cleanly
}

const size_t &  AI::get_score() const
{
  return (this->score);
}

void  AI::set_powerups(IPowerup *power)
{
  if (power->get_type() == SPEEDUP)
  {
    this->p = power;
    this->t = std::chrono::high_resolution_clock::now();
  }
  power->set_powerup(this);
}

void  AI::check_powerup()
{
  if (this->p != NULL && (std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count()
  - std::chrono::time_point_cast<std::chrono::seconds>(this->t).time_since_epoch().count()) >= 5)
  {
    this->p->unset_powerup(this);
    delete this->p;
    this->p = NULL;
  }
}

void  AI::move_up()
{
  std::vector<std::vector<Case> > &mp = this->map->getMap();
  float   tmp;

  if ((this->pos.y - this->speed) >= 0)
  {
    tmp = this->pos.y - this->speed;
    if (static_cast<int>(this->pos.y) != static_cast<int>(tmp))
      {
        if (mp[static_cast<int>(tmp)][this->pos.x]._state == Case::FREE)
        {
          if (mp[static_cast<int>(tmp)][this->pos.x]._state == Case::BOMB)
          {
            mp[static_cast<int>(this->pos.y)][this->pos.x]._state = Case::BOMB;
            if (static_cast<int>(tmp) != static_cast<int>(this->pos.y))
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
      }
    else
      this->pos.y = tmp;
  }
}

void  AI::move_down()
{
  std::vector<std::vector<Case> > &mp = this->map->getMap();
  float   tmp;

  if ((this->pos.y + this->speed) < mp.size())
  {
    tmp = this->pos.y + this->speed;
    if (static_cast<int>(this->pos.y) != static_cast<int>(tmp))
      {
        if (mp[static_cast<int>(tmp)][this->pos.x]._state == Case::FREE)
        {
          if (mp[static_cast<int>(tmp)][this->pos.x]._state == Case::BOMB)
          {
            mp[static_cast<int>(this->pos.y)][this->pos.x]._state = Case::BOMB;
            if (static_cast<int>(tmp) != static_cast<int>(this->pos.y))
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
      }
    else
      this->pos.y = tmp;
  }
}

void  AI::move_left()
{
  std::vector<std::vector<Case> > &mp = this->map->getMap();
  float   tmp;

  if ((this->pos.x - this->speed) >= 0)
  {
    tmp = this->pos.x - this->speed;
    if (static_cast<int>(this->pos.x) != static_cast<int>(tmp))
      {
        if (mp[this->pos.y][static_cast<int>(tmp)]._state == Case::FREE)
        {
          if (mp[static_cast<int>(tmp)][this->pos.x]._state == Case::BOMB)
          {
            mp[static_cast<int>(this->pos.y)][this->pos.x]._state = Case::BOMB;
            if (static_cast<int>(tmp) != static_cast<int>(this->pos.y))
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
      }
    else
      this->pos.x = tmp;
  }
}

void  AI::move_right()
{
  std::vector<std::vector<Case> > &mp = this->map->getMap();
  float   tmp;

  if ((this->pos.x + this->speed) < mp.size())
  {
    tmp = this->pos.x + this->speed;
    if (static_cast<int>(this->pos.x) != static_cast<int>(tmp))
      {
        if (mp[this->pos.y][static_cast<int>(tmp)]._state == Case::FREE)
        {
          if (mp[static_cast<int>(tmp)][this->pos.x]._state == Case::BOMB)
          {
            mp[static_cast<int>(this->pos.y)][this->pos.x]._state = Case::BOMB;
            if (static_cast<int>(tmp) != static_cast<int>(this->pos.y))
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
      }
    else
      this->pos.x = tmp;
  }
}
