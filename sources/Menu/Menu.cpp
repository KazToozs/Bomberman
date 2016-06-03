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
#include "ConfirmButton.hh"
#include "BackButton.hh"

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

Gui *Menu::getGui() const { return this->gui; }

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
	Func_Ptr btn = NULL;

	if (buttons.size() > _pos)
		btn = this->buttons[_pos]->action();
	if (btn)
		(this->*btn)();
	else
		createMainMenu();
	_Mtx->unlock();
}

void Menu::setEndGame() {
	this->id_menu = MAIN_MENU;
	createMainMenu();
	this->gui->StopGame();
}

void Menu::CreateMultiPlayer() {
	clearList();
	this->id_menu = SOLO_MULTI;
	pushBackList(new IAButton("IA0", IAButton::IA_0, this, true));
	pushBackList(new IAButton("IA1", IAButton::IA_1, this, true));
	pushBackList(new IAButton("IA2", IAButton::IA_2, this, true));
	pushBackList(new BackButton("Retour", this));
}

void Menu::BackMenu() {
	clearList();
	if (this->id_menu == SOLO_MULTI || this->id_menu == OPTIONS
		|| this->id_menu == EXIT)
		createMainMenu();
}

void Menu::CreateSoloPlayer() {
	clearList();
	this->id_menu = SOLO_MULTI;
	pushBackList(new IAButton("IA1", IAButton::IA_1, this, false));
	pushBackList(new IAButton("IA2", IAButton::IA_2, this, false));
	pushBackList(new IAButton("IA3", IAButton::IA_3, this, false));
	pushBackList(new BackButton("Retour", this));
}

void Menu::LaunchGame() {
	clearList();
	createMainMenu();
}

void Menu::PutOptions() {
	clearList();
	this->id_menu = OPTIONS;
	pushBackList(new IAButton("IA1", IAButton::IA_1, this, true));
	pushBackList(new IAButton("IA2", IAButton::IA_2, this, true));
	pushBackList(new IAButton("IA3", IAButton::IA_3, this, true));
	pushBackList(new BackButton("Retour", this));
}

void Menu::ConfirmExit() {
	clearList();
	this->id_menu = EXIT;
	pushBackList(new ConfirmButton("Oui", ConfirmButton::YES, this));
	pushBackList(new ConfirmButton("Non", ConfirmButton::NO, this));
}

void Menu::ExitGame() {
	this->gui->CloseWindows();
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

	name = (this->buttons.size() > 0) ? this->buttons[_pos]->getName() : "Null";
	_Mtx->unlock();
	return (name);
}

void Menu::createMainMenu() {
	this->buttons.push_back(new PlayerButton("Solo", PlayerButton::SOLO, this));
	this->buttons.push_back(new PlayerButton("Multi", PlayerButton::MULTI, this));
	this->buttons.push_back(new ExitButton(this));
}
