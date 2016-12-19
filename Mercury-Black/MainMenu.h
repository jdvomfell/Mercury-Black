#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameState.h"
#include "Buttons.h"

#define MENU_FONT_SIZE 130
#define MENU_TITLE_SIZE 450

#define NEW_GAME 1
#define LOAD_GAME 2
#define EDITOR 3
#define OPTIONS 4
#define QUIT 5

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

	sf::Color hText;
	sf::Color uText;

	static MainMenu mainMenu;

	sf::Font menuFont;

	std::vector <GUI *> buttons;

	GUI_NewGame newButton;
	GUI_LoadGame loadButton;
	GUI_Editor editorButton;
	GUI_Options optionsButton;
	GUI_Quit quitButton;

	sf::Text title;

};

#endif