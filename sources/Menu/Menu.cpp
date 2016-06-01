//
// Menu.cpp for  in /home/liege_m/rendu/cpp_indie_studio/sources/Menu
//
// Made by maxime liege
// Login   <liege_m@epitech.net>
//
// Started on  Thu Apr 28 14:12:56 2016 maxime liege
// Last update Wed May 18 13:35:38 2016 maxime liege
//

#include "Menu.hh"

#include <iostream>

#include "ExitButton.hh"
#include "PlayerButton.hh"
#include "OptionButton.hh"
#include "IAButton.hh"
#include "ContinueButton.hh"

Menu::Menu(Gui *gui) {
	this->id_menu = MAIN_MENU;
	this->_pos = 0;
	this->_Mtx = new std::mutex();
	this->gui = gui;
	createMainMenu();
}

Menu::~Menu() { this->clearList(); }

void Menu::clearList() {
	std::vector<IButtons *>::iterator it;

	it = buttons.begin();
	while (it != buttons.end()) {
		delete (*it);
		it++;
	}
	this->buttons.clear();
	this->_pos = 0;
}

void Menu::affList() {
	std::vector<IButtons *>::iterator it;

	it = buttons.begin();
	while (it != buttons.end()) {
		std::cout << (*it)->getName() << std::endl;
		it++;
	}
}

void Menu::GoUp() {
	_Mtx->lock();
	this->_pos = (_pos - 1 < 0) ? 0 : _pos - 1;
	_Mtx->unlock();
}
void Menu::GoDown() {
	_Mtx->lock();
	this->_pos = (_pos + 1 < buttons.size()) ? _pos + 1 : buttons.size() - 1;
	_Mtx->unlock();
}
void Menu::Action() {
	_Mtx->lock();
	Func_Ptr btn = this->buttons[_pos]->action();
	(this->*btn)();
	_Mtx->unlock();
}

void Menu::CreateMultiPlayer() {
	clearList();
	pushBackList(new IAButton("IA1", IAButton::IA_1, this, true));
	pushBackList(new IAButton("IA2", IAButton::IA_2, this, true));
	pushBackList(new IAButton("IA3", IAButton::IA_3, this, true));
}

void Menu::StartGame() {
	this->id_menu = GAME;
}

void Menu::pushBackList(IButtons *button) { this->buttons.push_back(button); }

const Menu::ID_MENU Menu::getId() const {
	Menu::ID_MENU id = this->id_menu;
	return id;
}

const IButtons *Menu::getCurrentButton() const { return this->buttons[_pos]; }

const std::string Menu::getButtonName() const {
	std::string name;
	_Mtx->lock();
	name = this->buttons[_pos]->getName();
	_Mtx->unlock();
	return (name);
}

void Menu::createMainMenu() {
	this->buttons.push_back(new ContinueButton(this));
	this->buttons.push_back(new PlayerButton("Solo", PlayerButton::SOLO, this));
	this->buttons.push_back(new PlayerButton("Multi", PlayerButton::MULTI, this));
	this->buttons.push_back(new OptionButton(this));
	this->buttons.push_back(new ExitButton(this));
}
