#include "OptionsMenu.h"
#include <string>
#include <iostream>

OptionsMenu OptionsMenu::optionsMenu;

void OptionsMenu::init() {

	title = sf::Text("Options", engine->textureManager.font, OPTION_TITLE_SIZE);
	title.setFillColor(sf::Color::Black);
	title.setOutlineThickness(5);
	title.setOutlineColor(uText);
	title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);

	musicToggle = TextButton("Music", 0, 0, OPTION_FONT_SIZE, &engine->textureManager.font, &doNothing);
	sfxToggle = TextButton("SFX", 0, 0, OPTION_FONT_SIZE, &engine->textureManager.font, &doNothing);
	changeBinding = TextButton("Key Bindings", 0, 0, OPTION_FONT_SIZE, &engine->textureManager.font, &changeToKeyBindings);

	guiHandler.buttons.resize(3);
	guiHandler.buttons = { &musicToggle, &sfxToggle, &changeBinding };

	view = engine->window.getDefaultView();
	engine->window.setView(view);

	title.setPosition(view.getCenter().x, view.getCenter().y - (view.getSize().y / 5));

	musicToggle.text.setPosition(view.getCenter().x - (view.getSize().x / 2) * 2 / 3 - 50, title.getPosition().y + (view.getSize().y / 2) * 2 / 3);
	sfxToggle.text.setPosition(view.getCenter().x - (view.getSize().x / 2) * 2 / 3 - 50, title.getPosition().y + (view.getSize().y / 2));
	changeBinding.text.setPosition(view.getCenter().x + (view.getSize().x / 2) * 1 / 3, title.getPosition().y + (view.getSize().y / 2) * 2 / 3);

}

void OptionsMenu::clean() {

}

void OptionsMenu::handleEvent() {

	sf::Event event;

	if (engine->window.pollEvent(event)) {

		switch (event.type) {

		case sf::Event::MouseMoved:

			guiHandler.isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
			break;

		case sf::Event::MouseButtonPressed:

			if (event.mouseButton.button == sf::Mouse::Left) {

				for (size_t i = 0; i < guiHandler.buttons.size(); i++) {

					if (guiHandler.buttons[i]->isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
						guiHandler.buttons[i]->interact(engine);

				}

			}

		case sf::Event::KeyPressed:

			if (event.key.code == sf::Keyboard::Escape)
				engine->popState();

			break;

		case sf::Event::Closed:
			engine->quit();
			break;

		}

	}
}

void OptionsMenu::update(const float dt) {

}

void OptionsMenu::render(const float dt) {

	engine->window.clear(sf::Color(248, 240, 225));

	guiHandler.draw(&engine->window);

	engine->window.draw(title);
}