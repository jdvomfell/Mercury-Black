#include "Editor.h"

#include <iostream>
#include <fstream>
#include <string>

#include "MainMenu.h"
#include "Game.h"

Editor Editor::editor;

void Editor::init() {
	
	cursor = Cursor();

	showLines = true;
	mode = POINT;
	tool = PLACE;

	font.loadFromFile("ZenzaiItachi.ttf");

	modeText = sf::Text("Mode: Point", font, 60);
	modeText.setFillColor(sf::Color::Black);

	toolText = sf::Text("Tool: Place", font, 60);
	toolText.setFillColor(sf::Color::Black);

	collisionMap.load();
	collisionMap.updateVerticies();

	objectMap = ObjectMap(&engine->textureManager);

}

void Editor::clean() {

	collisionMap.clean();
	objectMap.clean();

}

void Editor::pause() {

}

void Editor::resume() {

}

void Editor::handleEvent() {

	sf::Event event;

	engine->window.pollEvent(event);

	switch (event.type) {

	case sf::Event::Closed:
		
		engine->quit();
		
		break;

	case sf::Event::MouseButtonPressed:

		if (event.mouseButton.button == sf::Mouse::Left) {
			if(mode == POINT)
				collisionMap.insert(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
			if (mode == OBJECT)
				objectMap.insert(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
		}

		if (event.mouseButton.button == sf::Mouse::Right) {

			if (mode == POINT) {
				cursor.rect.setOutlineColor(sf::Color::Black);
				collisionMap.selected = collisionMap.findClosest(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)).x);

				if (collisionMap.selected != collisionMap.map.end()) {
					cursor.rect.setPosition(collisionMap.selected->second->position);
					cursor.rect.setOutlineColor(sf::Color::Red);
				}
			}
		}

		break;

	case sf::Event::KeyPressed:
		
		if (event.key.code == sf::Keyboard::Escape)
			engine->changeState(MainMenu::instance(engine));

		if (event.key.code == sf::Keyboard::Tab)
			engine->changeState(Game::instance(engine));

		if (event.key.code == sf::Keyboard::Delete) {
			if (mode == POINT) {
				cursor.rect.setOutlineColor(sf::Color::Transparent);
				collisionMap.remove();
			}
		}

		if (event.key.code == sf::Keyboard::A)
			doLeft = true;
		if (event.key.code == sf::Keyboard::D)
			doRight = true;
		if (event.key.code == sf::Keyboard::W)
			doUp = true;
		if (event.key.code == sf::Keyboard::S)
			doDown = true;

		if (event.key.code == sf::Keyboard::L)
			showLines = !showLines;

		if (event.key.code == sf::Keyboard::J)
			collisionMap.save();
		if (event.key.code == sf::Keyboard::K)
			collisionMap.load();

		if (event.key.code == sf::Keyboard::M)
			rotateMode();
		if (event.key.code == sf::Keyboard::N)
			rotateTool();

		if (mode == OBJECT) {
			if (event.key.code == sf::Keyboard::T)
				objectMap.changeObject();
			cursor.sprite.setTexture(engine->textureManager.textures.find(objectMap.object.textureName)->second);
			cursor.sprite.setOrigin(cursor.sprite.getLocalBounds().width / 2, cursor.sprite.getLocalBounds().height / 2);
		}

		break;

	case sf::Event::KeyReleased:
		if (event.key.code == sf::Keyboard::A)
			doLeft = false;
		if (event.key.code == sf::Keyboard::D)
			doRight = false;
		if (event.key.code == sf::Keyboard::W)
			doUp = false;
		if (event.key.code == sf::Keyboard::S)
			doDown = false;
		break;
	}

}

void Editor::update(const float dt) {

	if (doLeft == true)
		viewVelX = -15.0f;
	else if (doRight == true)
		viewVelX = 15.0f;
	else
		viewVelX = 0.0f;

	if (doUp == true)
		viewVelY = -15.0f;
	else if (doDown == true)
		viewVelY = 15.0f;
	else
		viewVelY = 0.0f;

	view.setSize(sf::Vector2f(engine->window.getDefaultView().getSize().x * 2, engine->window.getDefaultView().getSize().y * 2));
	engine->window.setView(view);

	modeText.setPosition(view.getCenter().x - view.getSize().x / 2 + 50, view.getCenter().y - view.getSize().y / 2 + 50);
	toolText.setPosition(view.getCenter().x - view.getSize().x / 2 + 50, view.getCenter().y - view.getSize().y / 2 + 200);

	view.move(viewVelX, viewVelY);

}

void Editor::render(const float dt) {

	for (objectMap.selected = objectMap.map.begin(); objectMap.selected != objectMap.map.end(); objectMap.selected++)
		engine->window.draw(objectMap.selected->second->sprite);

	if (showLines)
		engine->window.draw(collisionMap.lines);

	if(mode == POINT)
		engine->window.draw(cursor.rect);

	engine->window.draw(modeText);
	engine->window.draw(toolText);
}

void Editor::rotateMode() {
	
	if (mode == POINT) {
		mode = OBJECT;
		modeText.setString("Mode: Object");
	}
	else if (mode == OBJECT) {
		mode = POINT;
		modeText.setString("Mode: Point");
	}
	else {
		mode = POINT;
		modeText.setString("Mode: Point");
	}

}

void Editor::rotateTool() {

	if (tool == PLACE) {
		tool = DELETE;
		toolText.setString("Tool: Delete");
	}
	else if (tool == DELETE) {
		tool = MOVE;
		toolText.setString("Tool: Move");
	}
	else {
		tool = PLACE;
		toolText.setString("Tool: Place");
	}

}

Cursor::Cursor() {

	rect.setOutlineColor(sf::Color::Transparent);
	rect.setFillColor(sf::Color::Transparent);
	rect.setSize(sf::Vector2f(15, 15));
	rect.setOutlineThickness(3);
	rect.setOrigin(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2);
	rect.setPosition(0, 0);

	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

}