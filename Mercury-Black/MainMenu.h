#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameState.h"
#include <SDL_ttf.h>

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

	TTF_Font * font;

	SDL_Surface * newGame;
	SDL_Surface * loadGame;
	SDL_Surface * editor;
	SDL_Surface * options;
	SDL_Surface * quit;

	SDL_Color unhighlited;
	SDL_Color highlited;

};

#endif