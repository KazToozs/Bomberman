//
// game.cpp for bombi in /Users/pallua_j/rendu/CPP/cpp_indie_studio/player/src/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Tue May  3 17:16:51 2016 Jules Palluau
// Last update Tue May 10 10:46:45 2016 Jules Palluau
//

#include "Game.hh"
#include "IPlayer.hh"
#include "Player.hh"
#include "Bomb.hh"
#include "Map.hh"
#include "AI.hh"
#include "Keybind.hh"
#include <iostream>
#include <thread>

class AI;

Game::Game(const int &nb_ia, const int &nb_real, const int &size) {
  //  this->keybind = key;
  this->size = size;
  this->nb_ia = nb_ia;
  this->nb_real = nb_real;
  this->mtx = new std::mutex();
  this->map = NULL;
  this->th = NULL;
}

Game::Game(const Game &gm) {
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

Game::~Game() {
  delete this->mtx;
  if (this->map != NULL) delete this->map;
  if (this->th != NULL) delete this->th;
  this->players.clear();
}

const Game &Game::operator=(const Game &gm) {
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

void Game::init(Keybind *keys) {
//  std::cout << "géty" << std::endl;
  this->map = new Map(this->size, this->size);
//  std::cout << "fag" << std::endl;
  for (size_t x = 0; x < this->nb_real; x++) {
    this->players.push_back(new Player(this->map, x + 1, keys));
    players[x]->init();
  }
  /*for (size_t x = 0; x < this->nb_ia; x++)
  {
    this->players.push_back(new AI(this->map, (x + this->nb_real + 1)));
    players[x + this->nb_real]->init();
  }*/
  // luabridge::LuaRef playerTable = luabridge::newTable(L);
  // for(size_t i = 0; i < this->players.size(); ++i)
  // {
  //   luabridge::LuaRef innerTable = luabridge::newTable(L);
  //   innerTable[1] = this->players[i].get_pos().x;
  //   innerTable[2] = this->players[i].get_pos().y;
  //   playerTable[i + 1] = innerTable;
  // }
  // luabridge::setGlobal(L, playerTable, "playerTable");
  // TODO create ia
}

void Game::loop() {
  int i = 0; /* delete this */

    std::cout << "in loop" << std::endl;
  while (this->check_finish() == false) {
    this->mtx->lock();
    for (size_t x = 0; x < this->players.size(); x++) {
      if (this->players[x]->is_alive() == true) {
        this->players[x]->check_bombs();
        if (this->players[x]->check_alive() == true)
          this->players[x]->do_action();
      }
    }
    i++;
//    std::cout << "---- Turn: " << i << std::endl;
  //  std::cout << "----- AFTER -----" << std::endl;
   // this->map->print();
    this->mtx->unlock();
   // sleep(0.2);
  }
}

void    Game::start()
{
   this->lp = new std::thread([&] { this->loop(); });
}

void Game::lock() const { this->mtx->lock(); }

void Game::unlock() const { this->mtx->unlock(); }

bool Game::check_finish() {
  int cpt;

  cpt = 0;
  for (size_t x = 0; x < this->players.size(); x++) {
    if (players[x]->check_alive() == false) cpt++;
    if (cpt == (this->nb_ia + this->nb_real) - 1) return (true);
  }
  return (false);
}

const IPlayer *Game::who_alive() const {
  for (size_t x = 0; x < this->players.size(); x++) {
    if (players[x]->is_alive() == true) return (this->players[x]);
  }
  return (NULL);
}

const std::vector<IPlayer *> &Game::get_players() const {
  return (this->players);
}

void Game::check_bombs() {
  for (size_t x = 0; x < this->players.size(); x++)
    this->players[x]->check_bombs();
}

std::vector<Bomb *> Game::get_bombs() const {
  std::vector<Bomb *> ret;
  std::vector<Bomb *> tmp;

  for (size_t x = 0; x < this->players.size(); x++) {
    tmp = this->players[x]->get_bombs();
    ret.insert(ret.end(), tmp.begin(), tmp.end());
  }
  return (ret);
}

Map *Game::get_map() const { return (this->map); }

void Game::set_map(Map *mp) { this->map = mp; }

void Game::set_players(const std::vector<IPlayer *> &pl) { this->players = pl; }
