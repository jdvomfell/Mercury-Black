#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "GameState.h"
#include "Buttons.h"

#define MENU_FONT_SIZE 70
#define MENU_TITLE_SIZE 200

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

	sf::Color hText;
	sf::Color uText;

	static PauseMenu pauseMenu;

	std::vector <GUI *> buttons;

	Button newButton;
	Button loadButton;
	Button editorButton;
	Button hitboxEditorButton;
	Button optionsButton;
	Button quitButton;

	sf::Text title;

	sf::View view;

};

#endif