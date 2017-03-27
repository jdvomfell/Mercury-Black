#include "MainMenu.h"
#include <iostream>

MainMenu MainMenu::mainMenu;

void MainMenu::init() {

	title = sf::Text("Mercury Black", engine->textureManager.font, MENU_TITLE_SIZE);
	title.setFillColor(sf::Color::Black);
	title.setOutlineThickness(5);
	title.setOutlineColor(sf::Color(100, 100, 100, 255));
	title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);

	newButton = TextButton("New", 0, 0, MENU_FONT_SIZE, &engine->textureManager.font, &changeToGame);
	loadButton = TextButton("Load", 0, 0, MENU_FONT_SIZE, &engine->textureManager.font, &doNothing);
	editorButton = TextButton("Editor", 0, 0, MENU_FONT_SIZE, &engine->textureManager.font, &changeToEditor);
	hitboxEditorButton = TextButton("HB Editor", 0, 0, MENU_FONT_SIZE, &engine->textureManager.font, &changeToHitboxEditor);
	optionsButton = TextButton("Options", 0, 0, MENU_FONT_SIZE, &engine->textureManager.font, &changeToOptionsMenu);
	quitButton = TextButton("Quit", 0, 0, MENU_FONT_SIZE, &engine->textureManager.font, &quitGame);

	guiHandler.buttons.resize(6);
	guiHandler.buttons = { &newButton, &loadButton, &editorButton, &hitboxEditorButton, &optionsButton, &quitButton };

	view = engine->window.getDefaultView();
	engine->window.setView(view);

	title.setPosition(view.getCenter().x, view.getCenter().y - (view.getSize().y / 5));

	newButton.text.setPosition(view.getCenter().x - (view.getSize().x / 2) * 1 / 3 - 135, title.getPosition().y + (view.getSize().y / 2) * 2 / 3);
	loadButton.text.setPosition(view.getCenter().x - 40, title.getPosition().y + (view.getSize().y / 2) * 2 / 3);
	editorButton.text.setPosition(view.getCenter().x + (view.getSize().x / 2) * 1 / 3 + 30, title.getPosition().y + (view.getSize().y / 2) * 2 / 3);
	hitboxEditorButton.text.setPosition(view.getCenter().x - 80, title.getPosition().y + (view.getSize().y / 2));
	optionsButton.text.setPosition(view.getCenter().x - (view.getSize().x / 2) * 1 / 2 - 175, title.getPosition().y + (view.getSize().y / 2));
	quitButton.text.setPosition(view.getCenter().x + (view.getSize().x / 2) * 1 / 2 + 50, title.getPosition().y + (view.getSize().y / 2));

	guiHandler.isSelected(sf::Vector2f(0, 0));

}

void MainMenu::clean() {

}

void MainMenu::handleEvent() {

	sf::Event event;

	if (engine->window.pollEvent(event)) {

		switch (event.type) {

		case sf::Event::MouseMoved:

			guiHandler.isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));

			break;

		case sf::Event::MouseButtonPressed:

			if (event.mouseButton.button == sf::Mouse::Left)
				guiHandler.interact(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)), engine);

			break;

		case sf::Event::Closed:
			engine->quit();
			break;

		}

	}

}

void MainMenu::update(const float dt) {



}

void MainMenu::render(const float dt) {

	guiHandler.draw(&engine->window);
	engine->window.draw(title);

}