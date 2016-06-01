#include "ContinueButton.hh"

ContinueButton::ContinueButton(Menu *menu)
  : name("Continue")
{
  this->menu = menu;
}

ContinueButton::~ContinueButton()
{

}

Func_Ptr			ContinueButton::action() const
{
	return NULL;
}

const std::string	&ContinueButton::getName() const
{
  return this->name;
}

bool			ContinueButton::getActive() const
{
  return this->isActive;
}
