#include "MainMenu.h"
#include <iostream>

MainMenu MainMenu::mainMenu;

void MainMenu::init() {

	hText = sf::Color::Black;
	uText = sf::Color(100, 100, 100, 255);

	title = sf::Text("Mercury Black", engine->textureManager.font, MENU_TITLE_SIZE);
	title.setFillColor(sf::Color::Black);
	title.setOutlineThickness(5);
	title.setOutlineColor(uText);
	title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);

	newButton = Button("New", 0, 0, uText, MENU_FONT_SIZE, &engine->textureManager.font, &changeToGame);
	loadButton = Button("Load", 0, 0, uText, MENU_FONT_SIZE, &engine->textureManager.font, &doNothing);
	editorButton = Button("Editor", 0, 0, uText, MENU_FONT_SIZE, &engine->textureManager.font, &changeToEditor);
	hitboxEditorButton = Button("HB Editor", 0, 0, uText, MENU_FONT_SIZE, &engine->textureManager.font, &changeToHitboxEditor);
	optionsButton = Button("Options", 0, 0, uText, MENU_FONT_SIZE, &engine->textureManager.font, &doNothing);
	quitButton = Button("Quit", 0, 0, uText, MENU_FONT_SIZE, &engine->textureManager.font, &quitGame);

	buttons.resize(6);
	buttons = { &newButton, &loadButton, &editorButton, &hitboxEditorButton, &optionsButton, &quitButton };

	view = engine->window.getDefaultView();
	engine->window.setView(view);

	title.setPosition(view.getCenter().x, view.getCenter().y - (view.getSize().y / 5));

	newButton.text.setPosition(view.getCenter().x - (view.getSize().x / 2) * 1/3, title.getPosition().y + (view.getSize().y / 2) * 2/3);
	loadButton.text.setPosition(view.getCenter().x, title.getPosition().y + (view.getSize().y / 2) * 2/3);
	editorButton.text.setPosition(view.getCenter().x + (view.getSize().x / 2) * 1/3, title.getPosition().y + (view.getSize().y / 2) * 2/3);
	hitboxEditorButton.text.setPosition(view.getCenter().x, title.getPosition().y + (view.getSize().y / 2));
	optionsButton.text.setPosition(view.getCenter().x - (view.getSize().x / 2) * 1/2, title.getPosition().y + (view.getSize().y / 2));
	quitButton.text.setPosition(view.getCenter().x + (view.getSize().x / 2) * 1/2, title.getPosition().y + (view.getSize().y / 2));

}

void MainMenu::clean() {

}

void MainMenu::handleEvent() {

	sf::Event event;

	if (engine->window.pollEvent(event)) {
		
		switch (event.type) {

		case sf::Event::MouseMoved:
			
			for (size_t i = 0; i < buttons.size(); i++) {
				
				if (buttons[i]->isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y))))
					buttons[i]->text.setFillColor(hText);
				else
					buttons[i]->text.setFillColor(uText);

			}
			break;

		case sf::Event::MouseButtonPressed:
			
			if (event.mouseButton.button == sf::Mouse::Left) {

				for (size_t i = 0; i < buttons.size(); i++) {

					if (buttons[i]->isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
						buttons[i]->interact(engine);

				}

			}
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

	for (size_t i = 0; i < buttons.size(); i++)
		engine->window.draw(buttons[i]->text);
	engine->window.draw(title);

}