#include "Editor.h"

#include <iostream>
#include <fstream>
#include <string>

Editor Editor::editor;

void Editor::init() {
	
	cursor.rect.setOutlineColor(sf::Color::Black);
	cursor.rect.setSize(sf::Vector2f(5, 5));
	cursor.rect.setOutlineThickness(5);
	cursor.rect.setPosition(10, 10);

	lines = sf::VertexArray(sf::LinesStrip, 0);
	showLines = true;
	showPoints = true;
	mode = POINT;
	tool = PLACE;

	font.loadFromFile("ZenzaiItachi.ttf");

	modeText = sf::Text("Mode: Point", font, 100);
	modeText.setFillColor(sf::Color::Black);

	toolText = sf::Text("Tool: Place", font, 100);
	toolText.setFillColor(sf::Color::Black);

	xPos = sf::Text("X Pos: ", font, 50);
	yPos = sf::Text("Y Pos: ", font, 50);

}

void Editor::clean() {

	std::map<int, Point*>::iterator it;

	for (it = pointMap.begin(); it != pointMap.end(); it++) {
		delete(it->second);
	}

	return;
}

void Editor::pause() {

}

void Editor::resume() {

}

void Editor::handleEvent(GameEngine* engine) {

	engine->window.setKeyRepeatEnabled(false);

	sf::Event event;

	engine->window.setKeyRepeatEnabled(false);
	engine->window.pollEvent(event);
	switch (event.type) {

	case sf::Event::Closed:
		engine->window.close();
		clean();
		exit(0);
		break;

	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::Escape)
			//engine->pushState(EditorTools::instance());
		if (event.key.shift == true)
			find = true;
		else
			find = false;
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
		if (event.key.code == sf::Keyboard::P)
			showPoints = !showPoints;
		if (event.key.code == sf::Keyboard::J)
			save();
		if (event.key.code == sf::Keyboard::K)
			load();
		if (event.key.code == sf::Keyboard::Return)
			doReturn = true;
		if (event.key.code == sf::Keyboard::Tab) {
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
		if (event.key.code == sf::Keyboard::T) {
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
		break;

	case sf::Event::KeyReleased:
		if (event.key.code == sf::Keyboard::A) {
			doLeft = false;
			leftReleased = true;
		}
		if (event.key.code == sf::Keyboard::D) {
			doRight = false;
			rightReleased = true;
		}
		if (event.key.code == sf::Keyboard::W)
			doUp = false;
		if (event.key.code == sf::Keyboard::S)
			doDown = false;
		break;
	}

}

void Editor::update(GameEngine* engine) {

	std::map<int, Point*>::iterator it;

	if (doLeft == true) {
		if (leftReleased && find == true) {
			if (pointMap.lower_bound(cursor.rect.getPosition().x) != pointMap.end()) {
				it = pointMap.lower_bound(cursor.rect.getPosition().x);
				if (it != pointMap.begin()) {
					it--;
					cursor.rect.setPosition(it->second->rect.getPosition());
					leftReleased = false;
				}
			}
		}
		else if (find == false)
			cursor.velX = -0.3;
	}

	if (doRight == true) {
		if (rightReleased && find == true) {
			if (pointMap.upper_bound(cursor.rect.getPosition().x) != pointMap.end()) {
				cursor.rect.setPosition(pointMap.upper_bound(cursor.rect.getPosition().x)->second->rect.getPosition());
				rightReleased = false;
			}
		}
		else if (find == false)
			cursor.velX = 0.3;
	}

	if (doUp == true) {
		if (mode == POINT) {
			if (tool == MOVE) {
				if (pointMap.find(cursor.rect.getPosition().x) != pointMap.end())
					pointMap.find(cursor.rect.getPosition().x)->second->rect.move(0.0f, -0.3f);
				lines.clear();
				for (it = pointMap.begin(); it != pointMap.end(); it++)
					lines.append(sf::Vertex(sf::Vector2f(it->second->x, it->second->rect.getPosition().y), sf::Color::Black));
			}
		}
		cursor.velY = -0.3;
	}

	if (doDown == true) {
		if (mode == POINT) {
			if (tool == MOVE) {
				if (pointMap.find(cursor.rect.getPosition().x) != pointMap.end())
					pointMap.find(cursor.rect.getPosition().x)->second->rect.move(0.0f, 0.3f);
				lines.clear();
				for (it = pointMap.begin(); it != pointMap.end(); it++)
					lines.append(sf::Vertex(sf::Vector2f(it->second->x, it->second->rect.getPosition().y), sf::Color::Black));
			}
		}
		cursor.velY = 0.3;
	}

	if (doReturn == true) {
		if (mode == POINT) {
			if (tool == PLACE) {
				tempPoint = new Point(cursor.rect.getPosition().x, cursor.rect.getPosition().y);
				pointMap.insert(std::make_pair(tempPoint->x, tempPoint));
			}

			else if (tool == DELETE) {
				if (pointMap.find(cursor.rect.getPosition().x) != pointMap.end())
					pointMap.erase(cursor.rect.getPosition().x);
			}

			lines.clear();
			for (it = pointMap.begin(); it != pointMap.end(); it++)
				lines.append(sf::Vertex(sf::Vector2f(it->second->rect.getPosition().x, it->second->rect.getPosition().y), sf::Color::Black));

		}

		doReturn = false;

	}

	view.setSize(sf::Vector2f(engine->window.getSize()));
	view.setCenter(cursor.rect.getPosition());
	engine->window.setView(view);

	modeText.setPosition(view.getCenter().x - engine->window.getSize().x / 2 + 50, view.getCenter().y - engine->window.getSize().y / 2 + 50);
	toolText.setPosition(view.getCenter().x - engine->window.getSize().x / 2 + 50, view.getCenter().y - engine->window.getSize().y / 2 + 200);

	cursor.rect.move(cursor.velX, cursor.velY);
	cursor.velX = 0;
	cursor.velY = 0;

}

void Editor::render(GameEngine* engine) {

	std::map<int, Point*>::iterator it;

	if (showLines)
		engine->window.draw(lines);

	if (showPoints) {
		for (it = pointMap.begin(); it != pointMap.end(); it++) {
			engine->window.draw(it->second->rect);
		}
	}

	engine->window.draw(cursor.rect);

	engine->window.draw(modeText);
	engine->window.draw(toolText);
}

void Editor::save() {

	// Save Points for collision map

	std::ofstream ofstream;

	std::string pointFilename = "point.dat";
	ofstream.open(pointFilename, std::ios::out | std::ios::binary);

	for (std::map<int, Point*>::iterator pit = pointMap.begin(); pit != pointMap.end(); pit++) {
		ofstream.write((char*)&pit->second->x, sizeof(int));
		ofstream.write((char*)&pit->second->y, sizeof(int));
	}

	ofstream.close();

	// Save objects for object map

	/*std::string objectFilename = "object.dat";
	ofstream.open(objectFilename);

	std::multimap<int, sf::Sprite*>::iterator oit;
	for (oit = objectMap.begin(); oit != objectMap.end(); oit++) {
	ofstream << oit->second;
	}

	ofstream.close();*/

}

void Editor::load() {

	pointMap.clear();

	std::ifstream ifstream;
	std::string pointFilename = "point.dat";
	ifstream.open(pointFilename, std::ios::in | std::ios::binary);

	Point * tempPoint;

	while (ifstream.peek() != EOF) {

		int tempX;
		int tempY;

		ifstream.read((char*)&tempX, sizeof(int));
		ifstream.read((char*)&tempY, sizeof(int));

		tempPoint = new Point(tempX, tempY);

		pointMap.insert(std::make_pair(tempX, tempPoint));

	}

	lines.clear();
	std::map<int, Point*>::iterator it;
	for (it = pointMap.begin(); it != pointMap.end(); it++)
		lines.append(sf::Vertex(sf::Vector2f(it->second->rect.getPosition().x, it->second->rect.getPosition().y), sf::Color::Black));

	ifstream.close();

}