#include "HitboxEditor.h"
#include "MainMenu.h"

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

	view.setSize(engine->window.getSize().x, engine->window.getSize().y);

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
		else if (event.key.code == sf::Keyboard::Up) {
			
			initialPosition.x = hitMap.select->second->box.getSize().x;
			initialPosition.y = hitMap.select->second->box.getSize().y + 5;
			
			hitMap.select->second->box.setSize(initialPosition);
			printf("%d\n", hitMap.select->second->box.getSize().x);
		}
		else if (event.key.code == sf::Keyboard::Down) {

			initialPosition.x = hitMap.select->second->box.getSize().x;
			initialPosition.y = hitMap.select->second->box.getSize().y - 5;

			hitMap.select->second->box.setSize(initialPosition);
			printf("%d\n", hitMap.select->second->box.getSize().x);
		}
		else if (event.key.code == sf::Keyboard::Right) {

			initialPosition.x = hitMap.select->second->box.getSize().x + 5;
			initialPosition.y = hitMap.select->second->box.getSize().y;

			hitMap.select->second->box.setSize(initialPosition);
			printf("%d\n", hitMap.select->second->box.getSize().x);
		}
		else if (event.key.code == sf::Keyboard::Left) {

			initialPosition.x = hitMap.select->second->box.getSize().x - 5;
			initialPosition.y = hitMap.select->second->box.getSize().y;

			hitMap.select->second->box.setSize(initialPosition);
			printf("%d\n", hitMap.select->second->box.getSize().x);
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
	std::string check;
	
	it = hitMap.select;
	check = textureID;

	while (1) {
		printf("check\n");
		check = engine->textureManager.getNextTextureID(check);
		if (!parser(textureID, check))
			break;
		hitMap.addHitbox(check, it->second->box, it->second->type);
	}
}

int HitboxEditor::parser(std::string textureID, std::string check) {

	for (int i = check.size() - 1; check[i] != '_'; i--) {
		printf("ohe yesssss\n");
		check = check.substr(0, check.size() - 1);
	}
	for (int i = 0; i < check.size(); i++) {
		if (check[i] != textureID[i]) {
			printf("%s %s not same fam\n", check.c_str(), textureID.c_str());
			return 0;
		}
	}
	printf("%s %s SAMMMEEE!\n", check.c_str(), textureID.c_str());
	return 1;
}

void HitboxEditor::update(const float dt) {

	sprite.setTexture(*engine->textureManager.getTexture(textureID));
	spriteBox.setSize(sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	spriteBox.setPosition(sprite.getPosition());
	//sprite.setOrigin(sprite.getPosition().x + sprite.getLocalBounds().width / 2, sprite.getPosition().y + sprite.getLocalBounds().height / 2);

}

void HitboxEditor::render(const float dt) {

	if (sprite.getGlobalBounds().height > engine->window.getSize().y)
		view.setSize(view.getSize().x, sprite.getGlobalBounds().height + 10);
	else
		view.setSize(view.getSize().x, engine->window.getSize().y + 10);

	if (sprite.getGlobalBounds().width > engine->window.getSize().x)
		view.setSize(sprite.getGlobalBounds().width + 10, view.getSize().y);
	else
		view.setSize(engine->window.getSize().x + 10, view.getSize().y);


	//spriteView.setSize(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
	view.setCenter(sprite.getPosition().x + sprite.getLocalBounds().width / 2, sprite.getPosition().y + sprite.getLocalBounds().height / 2);

	engine->window.draw(sprite);
	engine->window.setView(view);
	engine->window.draw(spriteBox);
	
	if (leftPlacing) {
		engine->window.draw(drawHitBox);
	}

	hitMap.draw(&engine->window, textureID);
}