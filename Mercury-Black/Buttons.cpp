#include "Buttons.h"
#include "Editor.h"
#include "Game.h"

GUI_NewGame::GUI_NewGame(float x, float y, sf::Color color, int size, sf::Font * font) {

	text = sf::Text("New", *font, size);
	text.setPosition(x, y);
	text.setFillColor(color);

}

void GUI_NewGame::interact(GameEngine * engine) {

	engine->changeState(Game::instance(engine));

}

GUI_LoadGame::GUI_LoadGame(float x, float y, sf::Color color, int size, sf::Font * font) {

	text = sf::Text("Load", *font, size);
	text.setPosition(x, y);
	text.setFillColor(color);

}

void GUI_LoadGame::interact(GameEngine * engine) {

}

GUI_Editor::GUI_Editor(float x, float y, sf::Color color, int size, sf::Font * font) {

	text = sf::Text("Editor", *font, size);
	text.setPosition(x, y);
	text.setFillColor(color);

}

void GUI_Editor::interact(GameEngine * engine) {

	engine->changeState(Editor::instance(engine));

}

GUI_Options::GUI_Options(float x, float y, sf::Color color, int size, sf::Font * font) {

	text = sf::Text("Options", *font, size);
	text.setPosition(x, y);
	text.setFillColor(color);

}

void GUI_Options::interact(GameEngine * engine) {

}

GUI_Quit::GUI_Quit(float x, float y, sf::Color color, int size, sf::Font * font) {

	text = sf::Text("Quit", *font, size);
	text.setPosition(x, y);
	text.setFillColor(color);



}

void GUI_Quit::interact(GameEngine * engine) {

	engine->quit();

}