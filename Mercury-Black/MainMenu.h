#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameState.h"
#include "Buttons.h"
#include "Metaball.h"

#define MENU_FONT_SIZE 70
#define MENU_TITLE_SIZE 200

#define NEW_GAME 1
#define LOAD_GAME 2
#define EDITOR 3
#define OPTIONS 4
#define QUIT 5

class MainMenu : public GameState {

public:

	void init();
	void clean();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);

	static MainMenu * instance(GameEngine * engine) { mainMenu.engine = engine; return &mainMenu; }

protected:

	MainMenu() {}

private:

	static MainMenu mainMenu;

	sf::Text title;

	sf::View view;

	MetaballHandler metaballHandler;

	GUI_Handler guiHandler;
	TextButton newButton;
	TextButton loadButton;
	TextButton editorButton;
	TextButton hitboxEditorButton;
	TextButton optionsButton;
	TextButton quitButton;

};

#endif