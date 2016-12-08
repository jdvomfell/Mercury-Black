#include "MainMenu.h"

MainMenu MainMenu::mainMenu;

void MainMenu::init() {

	printf("INIT\n");

}

void MainMenu::clean() {

}

void MainMenu::pause() {

}

void MainMenu::resume() {

}

void MainMenu::handleEvent(GameEngine * engine) {

	printf("HANDLE EVENTS\n");

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