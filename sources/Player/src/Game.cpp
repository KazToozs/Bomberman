//
// game.cpp for bombi in /Users/pallua_j/rendu/CPP/cpp_indie_studio/player/src/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Tue May  3 17:16:51 2016 Jules Palluau
// Last update Mon May  9 13:58:00 2016 Jules Palluau
//

#include "../include/Game.hh"
#include "../include/IPlayer.hh"
#include "../include/Player.hh"
#include "../include/Bomb.hh"
#include "../../Map/Map.hh"
#include <iostream>

Game::Game(const int &nb_ia, const int &nb_real, const int &size)
{
//  this->keybind = key;
  this->size = size;
  this->nb_ia = nb_ia;
  this->nb_real = nb_real;
  this->mtx = new std::mutex();
  this->map = NULL;
  this->th = NULL;
}

Game::Game(const Game &gm)
{
  this->keybind = gm.keybind;
  this->size = gm.size;
  this->nb_ia = gm.nb_ia;
  this->nb_real = gm.nb_real;
  this->size = gm.size;
  this->map = gm.map;
  this->mtx = gm.mtx;
  this->th = gm.th;
  this->players = gm.players;
}

Game::~Game()
{
  delete this->mtx;
  if (this->map != NULL)
    delete this->map;
  if (this->th != NULL)
    delete this->th;
  this->players.clear();
}

const Game &Game::operator=(const Game &gm)
{
  this->size = gm.size;
  this->nb_ia = gm.nb_ia;
  this->nb_real = gm.nb_real;
  this->size = gm.size;
  this->map = gm.map;
  this->mtx = gm.mtx;
  this->th = gm.th;
  this->players = gm.players;
  this->keybind = gm.keybind;
  return (*this);
}

void  Game::init()
{
  this->map = new Map(this->size, this->size);
  for (size_t x = 0; x < this->nb_real; x++)
  {
    this->players.push_back(new Player(this->mtx, this->map, x + 1));
    players[x]->init();
  }
  this->map->print();
  players[0]->put_bomb();
  std::cout << std::endl;
  sleep(3);
  players[0]->check_bombs();
  this->map->print();
  std::cout << std::endl;
  //TODO create ia
}

void  Game::start()
{
  //TODO loop function with init thread
}

void  Game::lock() const
{
  this->mtx->lock();
}

void  Game::unlock() const
{
  this->mtx->unlock();
}

bool  Game::check_finish()
{
  int cpt;

  cpt = 0;
  for (size_t x = 0; x < this->players.size(); x++)
  {
    if (players[x]->check_alive() == false)
      cpt++;
    if (cpt == (this->nb_ia + this->nb_real) - 1)
      return (true);
  }
  return (false);
}

const IPlayer *Game::who_alive() const
{
  for (size_t x = 0; x < this->players.size(); x++)
  {
      if (players[x]->is_alive() == true)
        return (this->players[x]);
  }
  return (NULL);
}

const std::vector<IPlayer *>  &Game::get_players() const
{
  return (this->players);
}

void  Game::check_bombs()
{
  for (size_t x = 0; x < this->players.size(); x++)
    this->players[x]->check_bombs();
}

std::vector<Bomb *> Game::get_bombs() const
{
  std::vector<Bomb *> ret;
  std::vector<Bomb *> tmp;

  for (size_t x = 0; x < this->players.size() ; x++)
  {
    tmp = this->players[x]->get_bombs();
    ret.insert(ret.end(), tmp.begin(), tmp.end());
  }
  return (ret);
}

Map   *Game::get_map() const
{
  return (this->map);
}

void  Game::set_map(Map *mp)
{
  this->map = mp;
}

void  Game::set_players(const std::vector<IPlayer *> &pl)
{
  this->players = pl;
}
