#include "HitboxEditor.h"

HitboxEditor HitboxEditor::hitboxEditor;

void HitboxEditor::init() {

	textureID = engine->textureManager.textures.begin()->first;
	drawHitBox.setFillColor(sf::Color::Transparent);
	drawHitBox.setOutlineThickness(5);
	drawHitBox.setOutlineColor(sf::Color::Cyan);
	spriteBox.setFillColor(sf::Color::Transparent);
	spriteBox.setOutlineThickness(3);
	spriteBox.setOutlineColor(sf::Color::Blue);
	hitMap.select = hitMap.map.lower_bound(textureID);

	leftPlacing = 0;
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

			if (hitMap.map.find(textureID) != hitMap.map.end()) {
				hitMap.select = hitMap.map.find(textureID);
			}
		}

		else if (event.key.code == sf::Keyboard::A) {

			sprite = sf::Sprite();

			textureID = engine->textureManager.getPrevTextureID(textureID);

			if (hitMap.map.find(textureID) != hitMap.map.end()) {
				hitMap.select = hitMap.map.find(textureID);
			}
		}
		else if (event.key.code == sf::Keyboard::J) {
			hitMap.save();
		}
		else if (event.key.code == sf::Keyboard::X) {
			copy(textureID);
		}
		else if (event.key.code == sf::Keyboard::K) {
			hitMap.load();
		}

		else if (event.key.code == sf::Keyboard::Delete) {
			if (hitMap.map.find(textureID) != hitMap.map.end()) {
				hitMap.select = hitMap.map.find(textureID);
				hitMap.deleteHitbox(textureID);
			}
		}

		else if (event.key.code == sf::Keyboard::C) {
			chooseCollision = 1;
		}
		
		else if (chooseCollision) {
			//Collision Box
			if (event.key.code == sf::Keyboard::Num1) {
				chooseHitbox = 0;
				drawHitBox.setOutlineColor(sf::Color::Cyan);
			}
			//Hurt Box
			else if (event.key.code == sf::Keyboard::Num2) {
				chooseHitbox = 1;
				drawHitBox.setOutlineColor(sf::Color::Magenta);
			}
			//Defence Box
			else if (event.key.code == sf::Keyboard::Num3) {
				chooseHitbox = 2;
				drawHitBox.setOutlineColor(sf::Color::Green);
			}
			//Damage Box
			else if (event.key.code == sf::Keyboard::Num4) {
				chooseHitbox = 3;
				drawHitBox.setOutlineColor(sf::Color::Red);
			}
			
			chooseCollision = 0;
		}
		break;
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left) {
			initialPosition = engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			drawHitBox.setPosition(initialPosition);
			drawHitBox.setSize(sf::Vector2f(0,0));

			//printf("I COORDS: %f %f\n", initialPosition.x, initialPosition.y);
			leftPlacing = 1;
			selected = 0;
		}
		else if (event.mouseButton.button == sf::Mouse::Right) {
			//if (hitMap.select != hitMap.map.upper_bound(textureID)) {
				printf("Yes\n");
				hitMap.cycleHitbox(textureID);
				printf("Oh yes babe\n");
			//}
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Left) {
			leftPlacing = 0;
			hitMap.addHitbox(textureID, drawHitBox, chooseCollision);
		}
		break;
	case sf::Event::MouseMoved:
		if (leftPlacing) {
			finalPosition = engine->window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
			drawHitBox.setSize(finalPosition - initialPosition);
			//printf("Left moved %f %f\n", finalPosition.x, finalPosition.y);
		}
		break;
	}
}
void HitboxEditor::copy(std::string textureID) {
	std::multimap <std::string, Hitbox *>::iterator it;
	it = hitMap.select;
	for (it = hitMap.map.begin(); it != hitMap.map.end(); it = hitMap.map.upper_bound(it->first)) {
		//textureID = it->first;
		printf("%s\n", it->first.c_str());
		hitMap.addHitbox(it->first, hitMap.select->second->box, hitMap.select->second->type);
	}
}
void HitboxEditor::update(const float dt) {

	sprite.setTexture(*engine->textureManager.getTexture(textureID));
	spriteBox.setSize(sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	spriteBox.setPosition(sprite.getPosition());
	//sprite.setOrigin(sprite.getPosition().x + sprite.getLocalBounds().width / 2, sprite.getPosition().y + sprite.getLocalBounds().height / 2);

}

void HitboxEditor::render(const float dt) {
	
	sf::View spriteView;
	//spriteView.setSize(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	spriteView.setCenter(sprite.getPosition().x + sprite.getLocalBounds().width / 2, sprite.getPosition().y + sprite.getLocalBounds().height / 2);

	engine->window.draw(sprite);
	engine->window.setView(spriteView);
	engine->window.draw(spriteBox);
	
	if (leftPlacing) {
		engine->window.draw(drawHitBox);
	}

	hitMap.draw(&engine->window, textureID);
}