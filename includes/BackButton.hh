#ifndef BACKBUTTON_H_
#define BACKBUTTON_H_

#include "Menu.hh"

class BackButton : public IButtons
{

public:

	BackButton(const std::string &name, Menu *menu);
	virtual ~BackButton();

	virtual Func_Ptr			action() const;
	virtual const std::string	&getName() const;
	virtual bool			getActive() const;

private:
	const std::string	name;
	bool			isActive;
	Menu			*menu;
};

#endif /* !BACKBUTTON_H_ */
