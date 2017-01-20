#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameState.h"
#include "Buttons.h"

#define MENU_FONT_SIZE 70
#define MENU_TITLE_SIZE 250

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

	void handleEvent();
	void update();
	void render();

	static MainMenu * instance(GameEngine * engine) { mainMenu.engine = engine; return &mainMenu; }

protected:

	MainMenu() {}

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