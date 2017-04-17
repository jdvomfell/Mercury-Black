#include "HitboxEditor.h"
#include "MainMenu.h"

HitboxEditor HitboxEditor::hitboxEditor;

void HitboxEditor::init() {

	positionText = sf::Text("Position: ", engine->textureManager.slideFont, 20);
	positionText.setFillColor(sf::Color::Black);

	topText = sf::Text("Top: ", engine->textureManager.slideFont, 20);
	topText.setFillColor(sf::Color::Black);
	leftText = sf::Text("Left: ", engine->textureManager.slideFont, 20);
	leftText.setFillColor(sf::Color::Black);
	rightText = sf::Text("Right: ", engine->textureManager.slideFont, 20);
	rightText.setFillColor(sf::Color::Black);
	bottomText = sf::Text("Bottom: ", engine->textureManager.slideFont, 20);
	bottomText.setFillColor(sf::Color::Black);
	sideText = sf::Text("Bottom: ", engine->textureManager.slideFont, 20);
	sideText.setFillColor(sf::Color::Black);

	textureID = engine->textureManager.textures.begin()->first;
	drawHitBox.setFillColor(sf::Color::Transparent);
	drawHitBox.setOutlineThickness(5);
	drawHitBox.setOutlineColor(sf::Color::Cyan);
	spriteBox.setFillColor(sf::Color::Transparent);
	spriteBox.setOutlineThickness(3);
	spriteBox.setOutlineColor(sf::Color::Blue);
	hitMap.load();
	hitMap.select = hitMap.map.lower_bound(textureID);

	view.setSize((float) engine->window.getSize().x, (float) engine->window.getSize().y);

	leftPlacing = 0;
}

void HitboxEditor::clean() {
	
	hitMap.clean();

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

			if (hitMap.select != hitMap.map.end())
				hitMap.colorHitbox(hitMap.select->second);
			hitMap.select = hitMap.map.find(textureID);

		}

		else if (event.key.code == sf::Keyboard::A) {

			sprite = sf::Sprite();

			textureID = engine->textureManager.getPrevTextureID(textureID);

			if (hitMap.select != hitMap.map.end())
				hitMap.colorHitbox(hitMap.select->second);
			hitMap.select = hitMap.map.find(textureID);

		}
		else if (event.key.code == sf::Keyboard::J) {
			hitMap.save();
		}
		else if (event.key.code == sf::Keyboard::K) {
			hitMap.load();
		}
		else if (event.key.code == sf::Keyboard::X) {
			copy(textureID);
		}
		else if (event.key.code == sf::Keyboard::Up) {
			
			if (hitMap.select == hitMap.map.end())
				break;

			switch (side) {
			case HITBOXSIDE_TOP:
				hitMap.select->second->box.move(0, -1.0f);
				hitMap.select->second->box.setSize(sf::Vector2f(hitMap.select->second->box.getSize().x, hitMap.select->second->box.getSize().y + 1.0f));
				break;
			case HITBOXSIDE_LEFT:
				hitMap.select->second->box.move(1.0f, 0);
				hitMap.select->second->box.setSize(sf::Vector2f(hitMap.select->second->box.getSize().x - 1.0f, hitMap.select->second->box.getSize().y));
				break;
			case HITBOXSIDE_RIGHT:
				hitMap.select->second->box.setSize(sf::Vector2f(hitMap.select->second->box.getSize().x + 1.0f, hitMap.select->second->box.getSize().y));
				break;
			case HITBOXSIDE_BOTTOM:
				hitMap.select->second->box.setSize(sf::Vector2f(hitMap.select->second->box.getSize().x, hitMap.select->second->box.getSize().y - 1.0f));
				break;
			}

			updateSelectText();

		}
		else if (event.key.code == sf::Keyboard::Down) {

			if (hitMap.select == hitMap.map.end())
				break;

			switch (side) {
			case HITBOXSIDE_TOP:
				hitMap.select->second->box.move(0, 1.0f);
				hitMap.select->second->box.setSize(sf::Vector2f(hitMap.select->second->box.getSize().x, hitMap.select->second->box.getSize().y - 1.0f));
				break;
			case HITBOXSIDE_LEFT:
				hitMap.select->second->box.move(-1.0f, 0);
				hitMap.select->second->box.setSize(sf::Vector2f(hitMap.select->second->box.getSize().x + 1.0f, hitMap.select->second->box.getSize().y));
				break;
			case HITBOXSIDE_RIGHT:
				hitMap.select->second->box.setSize(sf::Vector2f(hitMap.select->second->box.getSize().x - 1.0f, hitMap.select->second->box.getSize().y));
				break;
			case HITBOXSIDE_BOTTOM:
				hitMap.select->second->box.setSize(sf::Vector2f(hitMap.select->second->box.getSize().x, hitMap.select->second->box.getSize().y + 1.0f));
				break;
			}

			updateSelectText();

		}
		else if (event.key.code == sf::Keyboard::Right) {
			
			switch (side) {
			case HITBOXSIDE_TOP:
				side = HITBOXSIDE_LEFT;
				sideText.setString("Side: Left");
				break;
			case HITBOXSIDE_LEFT:
				side = HITBOXSIDE_RIGHT;
				sideText.setString("Side: Right");
				break;
			case HITBOXSIDE_RIGHT:
				side = HITBOXSIDE_BOTTOM;
				sideText.setString("Side: Bottom");
				break;
			case HITBOXSIDE_BOTTOM:
				side = HITBOXSIDE_TOP;
				sideText.setString("Side: Top");
				break;
			}

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

		else if (event.key.code == sf::Keyboard::Escape) {
			engine->changeState(MainMenu::instance(engine));
		}
		
		if (chooseCollision) {

			printf("Choose\n");
			//Collision Box
			if (event.key.code == sf::Keyboard::Num1) {
				hitboxType = HITBOXTYPE_COLLISION;
				drawHitBox.setOutlineColor(sf::Color::Cyan);
				chooseCollision = 0;
			}
			//Hurt Box
			else if (event.key.code == sf::Keyboard::Num2) {
				hitboxType = HITBOXTYPE_HURT;
				drawHitBox.setOutlineColor(sf::Color::Magenta);
				chooseCollision = 0;
			}
			//Defence Box
			else if (event.key.code == sf::Keyboard::Num3) {
				hitboxType = HITBOXTYPE_DEFENCE;
				drawHitBox.setOutlineColor(sf::Color::Green);
				chooseCollision = 0;
			}
			//Damage Box
			else if (event.key.code == sf::Keyboard::Num4) {
				hitboxType = HITBOXTYPE_DAMAGE;
				drawHitBox.setOutlineColor(sf::Color::Red);
				chooseCollision = 0;
			}
			
		}
		break;

	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left) {
			initialPosition = engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			printf("%f, %f", (engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)).x), (engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)).y));
			drawHitBox.setPosition(initialPosition);
			drawHitBox.setSize(sf::Vector2f(0,0));

			leftPlacing = 1;
		}
		else if (event.mouseButton.button == sf::Mouse::Right) {
			hitMap.cycleHitbox(textureID);
			updateSelectText();
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Left) {
			leftPlacing = 0;
			hitMap.addHitbox(textureID, drawHitBox, hitboxType);
		}
		break;
	case sf::Event::MouseMoved:
		if (leftPlacing) {
			finalPosition = engine->window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
			drawHitBox.setSize(finalPosition - initialPosition);
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
		check = engine->textureManager.getNextTextureID(check);
		
		if (!parser(textureID, check))
			break;
		
		hitMap.addHitbox(check, it->second->box, it->second->type);
	}
}

int HitboxEditor::parser(std::string textureID, std::string check) {

	/* Look For The Underscore Before The Frame Number */

	for (size_t i = check.size() - 1; check[i] != '_'; i--) {

		/* Get The Next Smaller String */

		check = check.substr(0, check.size() - 1);

		/* If This Texture Is Not Part Of An Animation Break */

		if (i == 0) {
			printf("No Underscore Found, Not Part Of An Animation\n");
			return 0;
		}
	
	}

	/* Make Sure The Texture Is Part Of The Same Animation */

	for (size_t i = 0; i < check.size(); i++) {

		if (check[i] != textureID[i]) {
			printf("%s, Is Not, %s Found A Different Animation\n", check.c_str(), textureID.c_str());
			return 0;
		}

	}

	printf("Found Another %s Frame\n", check.c_str());
	return 1;
}

void HitboxEditor::update(const float dt) {

	sprite.setTexture(*engine->textureManager.getTexture(textureID));
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setPosition(0, 0);
	
	positionText.setPosition(view.getCenter().x - engine->window.getSize().x / 2 + 30, view.getCenter().y - engine->window.getSize().y / 2 + 30);
	sideText.setPosition(view.getCenter().x - engine->window.getSize().x / 2 + 30, view.getCenter().y - engine->window.getSize().y / 2 + 120);
	topText.setPosition(view.getCenter().x - engine->window.getSize().x / 2 + 30, view.getCenter().y - engine->window.getSize().y / 2 + 150);
	leftText.setPosition(view.getCenter().x - engine->window.getSize().x / 2 + 30, view.getCenter().y - engine->window.getSize().y / 2 + 180);
	rightText.setPosition(view.getCenter().x - engine->window.getSize().x / 2 + 30, view.getCenter().y - engine->window.getSize().y / 2 + 210);
	bottomText.setPosition(view.getCenter().x - engine->window.getSize().x / 2 + 30, view.getCenter().y - engine->window.getSize().y / 2 + 240);
	spriteBox.setSize(sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	spriteBox.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);

}

void HitboxEditor::render(const float dt) {

	if (sprite.getGlobalBounds().height > (float) engine->window.getSize().y)
		view.setSize(view.getSize().x, sprite.getGlobalBounds().height + 10);
	else
		view.setSize(view.getSize().x, engine->window.getSize().y + 10);

	if (sprite.getGlobalBounds().width > (float) engine->window.getSize().x)
		view.setSize(sprite.getGlobalBounds().width + 10, view.getSize().y);
	else
		view.setSize((float) engine->window.getSize().x + 10, view.getSize().y);

	view.setCenter(sprite.getPosition().x, sprite.getPosition().y);

	engine->window.draw(sprite);
	engine->window.setView(view);
	engine->window.draw(spriteBox);
	
	if (leftPlacing) {
		engine->window.draw(drawHitBox);
	}

	hitMap.draw(&engine->window, textureID);

	engine->window.draw(positionText);
	engine->window.draw(topText);
	engine->window.draw(leftText);
	engine->window.draw(rightText);
	engine->window.draw(bottomText);
	engine->window.draw(sideText);
}

void HitboxEditor::updateSelectText() {

	if (hitMap.select == hitMap.map.end()) {
		positionText.setString("Position: ");
		topText.setString("Top: ");
		leftText.setString("Left: ");
		rightText.setString("Right: ");
		bottomText.setString("Bottom: ");
	}

	else {
		positionText.setString("Position:\n" + std::to_string(hitMap.select->second->box.getPosition().x) + "\n" + std::to_string(hitMap.select->second->box.getPosition().y));
		topText.setString("Top: " + std::to_string(hitMap.select->second->box.getGlobalBounds().top));
		leftText.setString("Left: " + std::to_string(hitMap.select->second->box.getGlobalBounds().left));
		rightText.setString("Right: " + std::to_string(hitMap.select->second->box.getGlobalBounds().left + hitMap.select->second->box.getGlobalBounds().width));
		bottomText.setString("Bottom: " + std::to_string(hitMap.select->second->box.getGlobalBounds().top + hitMap.select->second->box.getGlobalBounds().height));
	}

}