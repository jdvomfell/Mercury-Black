#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameState.h"

class MainMenu : public GameState {

public:

	void init();
	void clean();

	void pause();
	void resume();

	void handleEvent(GameEngine * engine);
	void update(GameEngine * engine);
	void render(GameEngine * engine);

	static MainMenu * instance() { return &mainMenu; }

private:

	static MainMenu mainMenu;

};

#endif