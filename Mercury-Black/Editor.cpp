#include "Editor.h"

#include <iostream>
#include <fstream>
#include <string>

#include "MainMenu.h"
#include "Game.h"

Editor Editor::editor;

void Editor::init() {

	selector = Selector();

	objectMap = ObjectMap(&engine->textureManager);
	objectMap.load();
	platformMap.load();

	zoom = 2.0f;
	view.setSize(sf::Vector2f(engine->window.getDefaultView().getSize().x * 2.0f, engine->window.getDefaultView().getSize().y * 2.0f));

	toolBox = ToolBox(engine);

}

void Editor::clean() {

	objectMap.clean();
	platformMap.clean();

}

void Editor::handleEvent() {

	sf::Event event;

	engine->window.pollEvent(event);

	switch (event.type) {

	case sf::Event::Closed:
		engine->quit();
		break;

	case sf::Event::MouseMoved:
		toolBox.highlightButtons(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
		engine->window.setView(view);
		break;

	case sf::Event::MouseWheelScrolled:

		if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
			zoom += event.mouseWheelScroll.delta;

		if (zoom < 1.0f)
			zoom = 1.0f;

		if (zoom > 10.0f)
			zoom = 10.0f;

		view.setSize(sf::Vector2f(engine->window.getDefaultView().getSize().x * zoom, engine->window.getDefaultView().getSize().y * zoom));

		break;

	case sf::Event::MouseButtonPressed:

		if (event.mouseButton.button == sf::Mouse::Left) {

			toolBox.clickButtons(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

			engine->window.setView(view);

			if (toolBox.getMode() == OBJECT) {
				objectMap.insert(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
			}

			else if (toolBox.getMode() == PLATFORM) {
				
				if (toolBox.getTool() == BOX_PLACE) {
					corner1 = engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				}

				else if (toolBox.getTool() == GROUND_PLACE) {
					if (platformMap.selected != platformMap.map.end())
						platformMap.selected->second->setOutlineThickness(0);

					platformMap.insertGround(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));

					if (platformMap.selected != platformMap.map.end()) {
						platformMap.selected->second->setOutlineThickness(5);
						platformMap.selected->second->setOutlineColor(sf::Color::Red);
					}
				}
				else
					platformMap.platformPoints.insert(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
			}

		}

		if (event.mouseButton.button == sf::Mouse::Right) {

			selector.rect.setOutlineColor(sf::Color::Transparent);

			if (toolBox.getMode() == PLATFORM) {

				if (platformMap.selected != platformMap.map.end())
					platformMap.selected->second->setOutlineThickness(0);
					
				platformMap.selected = platformMap.findClosest(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));

				if (platformMap.selected != platformMap.map.end()) {
					platformMap.selected->second->setOutlineThickness(5);
					platformMap.selected->second->setOutlineColor(sf::Color::Red);
				}

			}

			else if (toolBox.getMode() == OBJECT) {

				objectMap.selected = objectMap.findClosest(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));

				if (objectMap.selected != objectMap.map.end()) {
					selector.rect.setSize(sf::Vector2f(objectMap.selected->second->sprite.getLocalBounds().width, objectMap.selected->second->sprite.getLocalBounds().height));
					selector.rect.setOrigin(selector.rect.getSize() * 0.5f);
					selector.rect.setPosition(objectMap.selected->second->position.x, objectMap.selected->second->position.y);
					selector.rect.setOutlineColor(sf::Color::Blue);
				}

			}

		}
		
		if (toolBox.getMode() == PLATFORM && platformMap.selected != platformMap.map.end()) {
			toolBox.morphText1.setString("Point 0: X: " + std::to_string(platformMap.selected->second->getPoint(0).x) + "\nY: " + std::to_string(platformMap.selected->second->getPoint(0).y) + "\nFallthrough: N\\A\n");
		}

		else if (toolBox.getMode() == OBJECT && objectMap.selected != objectMap.map.end()) {
			toolBox.morphText1.setString("Point 0: X: "+std::to_string(objectMap.selected->second->position.x)+"\nY: "+std::to_string(objectMap.selected->second->position.y) + "\nFallthrough: N\\A\n");
		}

		break;

	case sf::Event::MouseButtonReleased:

		if (event.mouseButton.button == sf::Mouse::Left) {

			if (toolBox.getMode() == PLATFORM) {
				if (toolBox.getTool() == BOX_PLACE) {
					corner2 = engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					platformMap.insertBox(corner1, corner2);
				}
			}

		}

		break;

	case sf::Event::KeyPressed:
		
		if (event.key.code == sf::Keyboard::LShift)
			doSpeedUp = true;

		if (event.key.code == sf::Keyboard::Up) {
			objectMap.object.layer++;
			toolBox.morphText2.setString("Layer: " + std::to_string(objectMap.object.layer));
			printf("Layer: %d", objectMap.object.layer);
		}

		if (event.key.code == sf::Keyboard::Down) {
			if (objectMap.object.layer > 0) {
				objectMap.object.layer--;
				toolBox.morphText2.setString("Layer: " + std::to_string(objectMap.object.layer));
			}
			printf("Layer: %d", objectMap.object.layer);
		}

		if (event.key.code == sf::Keyboard::Escape)
			engine->changeState(MainMenu::instance(engine));

		if (event.key.code == sf::Keyboard::Tab)
			engine->changeState(Game::instance(engine));

		if (event.key.code == sf::Keyboard::Delete) {

			if (toolBox.getMode() == OBJECT)
				objectMap.remove();
			else if (toolBox.getMode() == PLATFORM) {
				if (toolBox.getTool() == PLACE)
					platformMap.platformPoints.remove();
				else
					platformMap.remove();
			}

			selector.rect.setOutlineColor(sf::Color::Transparent);

		}

		if (event.key.code == sf::Keyboard::Return) {

			if (toolBox.getMode() == PLATFORM)
				platformMap.insert();

		}

		if (event.key.code == sf::Keyboard::A)
			doLeft = true;
		if (event.key.code == sf::Keyboard::D)
			doRight = true;
		if (event.key.code == sf::Keyboard::W)
			doUp = true;
		if (event.key.code == sf::Keyboard::S)
			doDown = true;

		if (event.key.code == sf::Keyboard::J) {
			objectMap.save();
			platformMap.save();
		}
		if (event.key.code == sf::Keyboard::K) {
			objectMap.load();
			platformMap.load();
		}

		if (event.key.code == sf::Keyboard::M)
			toolBox.nextMode();
		if (event.key.code == sf::Keyboard::N)
			toolBox.nextTool();
		
		if (toolBox.getMode() == OBJECT) {
			if (event.key.code == sf::Keyboard::R) {
				objectMap.prevObject();
				toolBox.morphText3.setString(objectMap.object.textureName);
			}
			if (event.key.code == sf::Keyboard::T) {
				objectMap.nextObject();
				toolBox.morphText3.setString(objectMap.object.textureName);
			}

			else if (event.key.code == sf::Keyboard::I && objectMap.selected != objectMap.map.end())
				objectMap.objectFlipx(objectMap.selected->second);
			else if (event.key.code == sf::Keyboard::O && objectMap.selected != objectMap.map.end())
				objectMap.objectFlipy(objectMap.selected->second);
			else if (event.key.code == sf::Keyboard::Y && objectMap.selected != objectMap.map.end())
				objectMap.objectRotate(objectMap.selected->second, -.5);
			else if (event.key.code == sf::Keyboard::U && objectMap.selected != objectMap.map.end())
				objectMap.objectRotate(objectMap.selected->second, .5);
			else if (event.key.code == sf::Keyboard::Equal && objectMap.selected != objectMap.map.end())
				objectMap.objectScale(objectMap.selected->second, .05);
			else if (event.key.code == sf::Keyboard::Dash && objectMap.selected != objectMap.map.end())
				objectMap.objectScale(objectMap.selected->second, -.05);
		}
		break;

	case sf::Event::KeyReleased:
		if (event.key.code == sf::Keyboard::LShift)
			doSpeedUp = false;
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

	if (doSpeedUp) {
		if (doLeft == true)
			viewVelX = -30.0f;
		else if (doRight == true)
			viewVelX = 30.0f;
		else
			viewVelX = 0.0f;

		if (doUp == true)
			viewVelY = -30.0f;
		else if (doDown == true)
			viewVelY = 30.0f;
		else
			viewVelY = 0.0f;
	}
	else {
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
	}

	toolBox.update();

	view.move(viewVelX, viewVelY);

}

void Editor::render(const float dt) {

	engine->window.setView(view);
	
	objectMap.draw(&engine->window);
	platformMap.draw(&engine->window);
	platformMap.platformPoints.draw(&engine->window);
	engine->window.draw(selector.rect);

	toolBox.render();

	engine->window.setView(view);

}

void Editor::deselect() {

	selector.rect.setOutlineColor(sf::Color::Transparent);
	
	if (platformMap.selected != platformMap.map.end())
		platformMap.selected->second->setOutlineThickness(0);

	platformMap.selected = platformMap.map.end();
	objectMap.selected = objectMap.map.end();

}

Selector::Selector() {

	rect.setOutlineColor(sf::Color::Transparent);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(5);

}