//
// game.hh for bombi in /Users/pallua_j/rendu/CPP/cpp_indie_studio/player/include/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Tue May  3 16:49:18 2016 Jules Palluau
// Last update Mon May  9 13:59:28 2016 Jules Palluau
//

#ifndef _GAME_HH_
# define _GAME_HH_

#include <vector>
#include <thread>
#include <mutex>

class IPlayer;
class Bomb;
class Map;
class Gui;

class Game
{
private:
  Gui                     *keybind;
  int                     nb_ia;
  int                     nb_real;
  int                     size;
  Map                     *map;
  std::vector<IPlayer *>  players;
  std::thread             *th;
  std::mutex              *mtx;
public:
  Game(const int &nb_ia, const int &nb_real, const int &size);
  ~Game();
  Game(const Game &);
  const Game &operator=(const Game &);
  void  init();
  void  start();
  void  lock() const;
  void  unlock() const;
  bool  check_finish();
  const IPlayer *who_alive() const;
  const std::vector<IPlayer *> &get_players() const;
  void  check_bombs();
  std::vector<Bomb *> get_bombs() const;
  Map     *get_map() const;
  void  set_map(Map *);
  void  set_players(const std::vector<IPlayer *>&);
};

#endif /*!_GAME_HH_*/