#include "HitboxEditor.h"
#include "MainMenu.h"

HitboxEditor HitboxEditor::hitboxEditor;

void HitboxEditor::init() {

	textureID = engine->textureManager.textures.begin()->first;

}

void HitboxEditor::clean() {

}

void HitboxEditor::handleEvent() {

	sf::Event event;

	engine->window.pollEvent(event);

	switch (event.type) {

	case sf::Event::Closed:

		clean();
		
		engine->quit();

		break;

	case sf::Event::KeyPressed:

		if (event.key.code == sf::Keyboard::D) {

			sprite = sf::Sprite();

			textureID = engine->textureManager.getNextTextureID(textureID);

		}

		else if (event.key.code == sf::Keyboard::A) {

			sprite = sf::Sprite();

			textureID = engine->textureManager.getPrevTextureID(textureID);

		}

		if (event.key.code == sf::Keyboard::Escape)
			engine->changeState(MainMenu::instance(engine));

	}

}

void HitboxEditor::update(const float dt) {

	sprite.setTexture(*engine->textureManager.getTexture(textureID));

}

void HitboxEditor::render(const float dt) {

	engine->window.draw(sprite);

}