#include "MainMenu.h"

MainMenu MainMenu::mainMenu;

void MainMenu::init() {

	font = TTF_OpenFont("ZenzaiItachi.ttf", 24);

	unhighlited = { 150, 150, 150 };
	highlited = { 255, 255, 255 };

	newGame = TTF_RenderText_Solid(font, "New Game", unhighlited);
	loadGame = TTF_RenderText_Solid(font, "New Game", unhighlited);
	editor = TTF_RenderText_Solid(font, "New Game", unhighlited);
	options = TTF_RenderText_Solid(font, "New Game", unhighlited);
	quit = TTF_RenderText_Solid(font, "New Game", unhighlited);


}

void MainMenu::clean() {

}

void MainMenu::pause() {

}

void MainMenu::resume() {

}

void MainMenu::handleEvent(GameEngine * engine) {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		
		case SDL_QUIT:
			engine->quit();
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			
			case SDLK_ESCAPE:
				engine->popState();
				break;
			
			}
			break;
		
		}
	
	}

}

void MainMenu::update(GameEngine * engine) {

}

void MainMenu::render(GameEngine * engine) {

}