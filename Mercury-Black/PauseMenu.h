#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "GameState.h"
#include "Buttons.h"

#define PAUSE_FONT_SIZE 70
#define PAUSE_TITLE_SIZE 200

#define NEW_GAME 1
#define LOAD_GAME 2
#define EDITOR 3
#define OPTIONS 4
#define QUIT 5

class PauseMenu : public GameState {

public:

	void init();
	void clean();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);

	static PauseMenu * instance(GameEngine * engine) { pauseMenu.engine = engine; return &pauseMenu; }

protected:

	PauseMenu() {}

private:

	static PauseMenu pauseMenu;

	GUI_Handler guiHandler;
	TextButton resumeButton;
	TextButton optionsButton;
	TextButton mainMenuButton;
	TextButton quitButton;

	sf::Text title;

	sf::View view;

};

#endif