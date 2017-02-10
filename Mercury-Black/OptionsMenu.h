#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "GameState.h"
#include "Options.h"

class OptionsMenu : public GameState {

	void init();
	void clean();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);

	Options * options;

};

#endif