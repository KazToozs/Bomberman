//
// game.cpp for bombi in /Users/pallua_j/rendu/CPP/cpp_indie_studio/player/src/
//
// Made by Jules Palluau
// Login   <pallua_j@epitech.eu>
//
// Started on  Tue May  3 17:16:51 2016 Jules Palluau
// Last update Thu Jun  2 10:00:24 2016 pallua_j
//

#include "Game.hh"
#include "IPlayer.hh"
#include "Player.hh"
#include "Bomb.hh"
#include "Map.hh"
#include "AI.hh"
#include "Gui.hh"
#include "Keybind.hh"
#include "Game.hh"
#include <iostream>
#include <thread>

class AI;

Game::Game(const int &nb_ia, const int &nb_real, const int &size, Gui *g) {
	this->g = g;
	this->size = size;
	this->nb_ia = nb_ia;
	this->nb_real = nb_real;
	this->mtx = new std::mutex();
	this->map = NULL;
	this->th = NULL;
	this->actualiasation = true;
	this->_kill = false;
}

Game::Game(const Game &gm) {
	this->g = gm.g;
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
	_kill = true;
	std::this_thread::sleep_for(std::chrono::microseconds(1000000));
	if (this->map != NULL) delete this->map;
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
	this->g = gm.g;
	return (*this);
}

void Game::init(Keybind *keys) {
	this->map = new Map(this->size, this->size);
	for (size_t x = 0; x < this->nb_real; x++) {
		this->players.push_back(new Player(this->map, x + 1, keys, this));
		players[x]->init();
	}
	for (size_t x = 0; x < this->nb_ia; x++)
	{
		this->players.push_back(new AI(this->map, (x + this->nb_real + 1), this));
		players[x + this->nb_real]->init();
	}
}

void Game::loop() {
	while (this->check_finish() == false) {
		this->mtx->lock();
		for (size_t x = 0; x < this->players.size(); x++) {
			this->players[x]->check_bombs();
			if (this->players[x]->is_alive() == true) {
				if (this->players[x]->check_alive() == true)
				{
					this->players[x]->do_action();
					this->players[x]->check_powerup();
					this->players[x]->check_power_map();
				}
			}
		}
		this->mtx->unlock();
	}
	this->th = NULL;
}

void    Game::start()
{
	this->lp = new std::thread([&] { this->loop(); });
}

void Game::lock() const { this->mtx->lock(); }

void Game::unlock() const { this->mtx->unlock(); }

bool Game::check_finish() const {
	int cpt;

	if (_kill) {
		return (true);
	}
	cpt = 0;
	for (size_t x = 0; x < this->players.size(); x++) {
		if (players[x]->is_alive() == false) cpt++;
	}
	if (cpt == (this->nb_ia + this->nb_real) - 1) return (true);
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

const bool &Game::get_actualisation() const
{
	return (this->actualiasation);
}

void Game::set_actualisation(const bool &act)
{
	this->actualiasation = act;
}

Map *Game::get_map() const { return (this->map); }

void Game::set_map(Map *mp) { this->map = mp; }

void Game::set_players(const std::vector<IPlayer *> &pl) { this->players = pl; }
