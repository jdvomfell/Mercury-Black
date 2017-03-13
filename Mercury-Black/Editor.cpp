#include "Editor.h"

#include <iostream>
#include <fstream>
#include <string>

#include "MainMenu.h"
#include "Game.h"

Editor Editor::editor;

#define DEFAULT_TEXT_SIZE 30

void Editor::init() {

	selector = Selector();

	mode = PLATFORM;
	tool = PLACE;

	modeText = sf::Text("Mode: Platform", engine->textureManager.slideFont, DEFAULT_TEXT_SIZE);
	modeText.setFillColor(sf::Color::Black);

	toolText = sf::Text("Tool: Place", engine->textureManager.slideFont, DEFAULT_TEXT_SIZE);
	toolText.setFillColor(sf::Color::Black);

	textureText = sf::Text("", engine->textureManager.slideFont, DEFAULT_TEXT_SIZE);
	textureText.setFillColor(sf::Color::Black);

	morphText = sf::Text("", engine->textureManager.slideFont, DEFAULT_TEXT_SIZE);
	morphText.setFillColor(sf::Color::Black);

	objectMap = ObjectMap(&engine->textureManager);
	objectMap.load();
	textureText.setString(objectMap.object.textureName);

	platformMap.load();

	zoom = 2.0f;
	view.setSize(sf::Vector2f(engine->window.getDefaultView().getSize().x * 2.0f, engine->window.getDefaultView().getSize().y * 2.0f));

	toolBox.setFillColor(sf::Color::White);
	boxTool = IconButton(0, 0, engine->textureManager.getTexture("boxTool"), &doNothing);
	freeTool = IconButton(0, 0, engine->textureManager.getTexture("freeTool"), &doNothing);
	groundTool = IconButton(0, 0, engine->textureManager.getTexture("groundTool"), &doNothing);

	guiHandler.buttons.resize(3);
	guiHandler.buttons = { &boxTool, &freeTool, &groundTool };

	toolBoxView.setViewport(sf::FloatRect(0, 0, 0.2f, 1));
	toolBoxView.setSize(toolBoxView.getViewport().width * engine->window.getSize().x, toolBoxView.getViewport().height * engine->window.getSize().y);

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
		engine->window.setView(toolBoxView);
		guiHandler.isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));
		engine->window.setView(view);
		break;

	case sf::Event::MouseWheelScrolled:

		if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
			zoom += event.mouseWheelScroll.delta;

		if (zoom < 1.0f)
			zoom = 1.0f;

		if (zoom > 5.0f)
			zoom = 5.0f;

		view.setSize(sf::Vector2f(engine->window.getDefaultView().getSize().x * zoom, engine->window.getDefaultView().getSize().y * zoom));

		break;

	case sf::Event::MouseButtonPressed:

		if (event.mouseButton.button == sf::Mouse::Left) {

			engine->window.setView(toolBoxView);

			if (boxTool.isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
				mode = PLATFORM;
				tool = BOX;
				modeText.setString("Mode: Platform");
				toolText.setString("Tool: Box Place");
				break;
			}

			else if (freeTool.isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
				mode = PLATFORM;
				tool = PLACE;
				modeText.setString("Mode: Platform");
				toolText.setString("Tool: Free Place");
				break;
			}

			else if (groundTool.isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
				mode = PLATFORM;
				tool = GROUND;
				modeText.setString("Mode: Platform");
				toolText.setString("Tool: Ground Place");
				break;
			}

			engine->window.setView(view);

			if (mode == OBJECT) {
				objectMap.insert(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
			}

			else if (mode == PLATFORM) {
				
				if (tool == BOX) {
					corner1 = engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				}

				else if (tool == GROUND) {
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

			if (mode == PLATFORM) {

				if (platformMap.selected != platformMap.map.end())
					platformMap.selected->second->setOutlineThickness(0);
					
				platformMap.selected = platformMap.findClosest(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));

				if (platformMap.selected != platformMap.map.end()) {
					platformMap.selected->second->setOutlineThickness(5);
					platformMap.selected->second->setOutlineColor(sf::Color::Red);
				}

			}

			else if (mode == OBJECT) {

				objectMap.selected = objectMap.findClosest(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));

				if (objectMap.selected != objectMap.map.end()) {
					selector.rect.setSize(sf::Vector2f(objectMap.selected->second->sprite.getLocalBounds().width, objectMap.selected->second->sprite.getLocalBounds().height));
					selector.rect.setOrigin(selector.rect.getSize() * 0.5f);
					selector.rect.setPosition(objectMap.selected->second->position.x, objectMap.selected->second->position.y);
					selector.rect.setOutlineColor(sf::Color::Blue);
				}

			}

		}
		
		if (mode == PLATFORM && platformMap.selected != platformMap.map.end()) {
			morphText.setString("Point 0: X: " + std::to_string(platformMap.selected->second->getPoint(0).x) + " Y: " + std::to_string(platformMap.selected->second->getPoint(0).y) + "\nFallthrough: N\\A\n");
		}

		else if (mode == OBJECT && objectMap.selected != objectMap.map.end()) {
			morphText.setString("Point 0: X: "+std::to_string(objectMap.selected->second->position.x)+" Y: "+std::to_string(objectMap.selected->second->position.y) + "\nFallthrough: N\\A\n");
		}

		break;

	case sf::Event::MouseButtonReleased:

		if (event.mouseButton.button == sf::Mouse::Left) {

			if (mode == PLATFORM) {
				if (tool == BOX) {
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
			printf("Layer: %d", objectMap.object.layer);
		}

		if (event.key.code == sf::Keyboard::Down) {
			if (objectMap.object.layer > 0)
				objectMap.object.layer--;
			printf("Layer: %d", objectMap.object.layer);
		}

		if (event.key.code == sf::Keyboard::Escape)
			engine->changeState(MainMenu::instance(engine));

		if (event.key.code == sf::Keyboard::Tab)
			engine->changeState(Game::instance(engine));

		if (event.key.code == sf::Keyboard::Delete) {

			if (mode == OBJECT)
				objectMap.remove();
			else if (mode == PLATFORM) {
				if (tool == PLACE)
					platformMap.platformPoints.remove();
				else
					platformMap.remove();
			}

			selector.rect.setOutlineColor(sf::Color::Transparent);

		}

		if (event.key.code == sf::Keyboard::Return) {

			if (mode == PLATFORM)
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
			rotateMode();
		if (event.key.code == sf::Keyboard::N)
			rotateTool();
		
		if (mode == OBJECT) {
			if (event.key.code == sf::Keyboard::T) {
				objectMap.changeObject();
				textureText.setString(objectMap.object.textureName);
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

	engine->window.setView(view);

	modeText.setPosition(toolBoxView.getCenter().x - toolBoxView.getSize().x / 2.0f + 20, toolBoxView.getCenter().y - toolBoxView.getSize().y / 2.0f + 20);
	toolText.setPosition(toolBoxView.getCenter().x - toolBoxView.getSize().x / 2.0f + 20, toolBoxView.getCenter().y - toolBoxView.getSize().y / 2.0f + 70);
	textureText.setPosition(toolBoxView.getCenter().x - toolBoxView.getSize().x / 2.0f + 20, toolBoxView.getCenter().y - toolBoxView.getSize().y / 2.0f + 120);
	morphText.setPosition(toolBoxView.getCenter().x - toolBoxView.getSize().x / 2.0f + 20, toolBoxView.getCenter().y - toolBoxView.getSize().y / 2.0f + 170);
	toolBox.setPosition(toolBoxView.getCenter().x - toolBoxView.getSize().x / 2.0f, toolBoxView.getCenter().y - toolBoxView.getSize().y / 2);
	toolBox.setSize(toolBoxView.getSize());
	boxTool.sprite.setPosition(toolBoxView.getCenter().x + toolBoxView.getSize().x / 2.0f - 50, toolBox.getPosition().y);
	freeTool.sprite.setPosition(toolBox.getPosition().x + toolBox.getLocalBounds().width - 50, toolBox.getPosition().y + 50);
	groundTool.sprite.setPosition(toolBox.getPosition().x + toolBox.getLocalBounds().width - 50, toolBox.getPosition().y + 100);
	view.move(viewVelX, viewVelY);

}

void Editor::render(const float dt) {

	engine->window.setView(view);
	
	objectMap.draw(&engine->window);
	platformMap.draw(&engine->window);
	platformMap.platformPoints.draw(&engine->window);
	engine->window.draw(selector.rect);

	engine->window.setView(toolBoxView);

	engine->window.draw(toolBox);
	engine->window.draw(modeText);
	engine->window.draw(toolText);
	engine->window.draw(textureText);
	engine->window.draw(morphText);
	guiHandler.draw(&engine->window);

	engine->window.setView(view);

}

void Editor::rotateMode() {

	if (mode == PLATFORM) {
		mode = OBJECT;
		modeText.setString("Mode: Object");
		morphText.setString("Points: N\\A");
	}
	else if (mode == OBJECT) {
		mode = EVENT;
		modeText.setString("Mode: Event");
		morphText.setString("Points: N\\A");
	}
	else {
		mode = PLATFORM;
		modeText.setString("Mode: Platform");
		morphText.setString("Points: N\\A");
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
	else if (tool == MOVE) {
		tool = BOX;
		toolText.setString("Tool: Box");
	}
	else if (tool == BOX) {
		tool = GROUND;
		toolText.setString("Tool: Ground");
	}
	else {
		tool = PLACE;
		toolText.setString("Tool: Place");
	}

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