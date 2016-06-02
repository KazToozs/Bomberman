#include "BackButton.hh"

BackButton::BackButton(const std::string &name, Menu *menu)
	: name(name) {
	this->menu = menu;
}

BackButton::~BackButton() {}

Func_Ptr			BackButton::action() const {
	return &Menu::BackMenu;
}

const std::string	&BackButton::getName() const {
	return this->name;
}

bool			BackButton::getActive() const {
	return this->isActive;
}
