#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameState.h"

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

	void resized(int width, int height);
	void keyPressed(sf::Event* event, GameEngine* engine);


	static MainMenu * instance() { return &mainMenu; }

private:

	sf::Color hText;
	sf::Color uText;

	static MainMenu mainMenu;

	sf::Font menuFont;

	sf::Text newGame;
	sf::Text loadGame;
	sf::Text worldEditor;
	sf::Text options;
	sf::Text quit;

	sf::Text title;

	sf::Text test;

	int selector;

};

#endif