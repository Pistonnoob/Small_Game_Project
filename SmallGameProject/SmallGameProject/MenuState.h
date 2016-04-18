#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "GameState.h"
class MenuState :
	public GameState
{
private:
	int selected;
public:
	MenuState();
	~MenuState();
};

#endif