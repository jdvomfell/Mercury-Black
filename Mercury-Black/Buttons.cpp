#include "Buttons.h"

GUI_NewGame::GUI_NewGame(float x, float y, sf::Color color, int size, sf::Font * font) {

	text = sf::Text("New", *font, size);
	text.setPosition(x, y);
	text.setFillColor(color);

}

GUI_LoadGame::GUI_LoadGame(float x, float y, sf::Color color, int size, sf::Font * font) {

	text = sf::Text("Load", *font, size);
	text.setPosition(x, y);
	text.setFillColor(color);

}

GUI_Editor::GUI_Editor(float x, float y, sf::Color color, int size, sf::Font * font) {

	text = sf::Text("Editor", *font, size);
	text.setPosition(x, y);
	text.setFillColor(color);

}

GUI_Options::GUI_Options(float x, float y, sf::Color color, int size, sf::Font * font) {

	text = sf::Text("Options", *font, size);
	text.setPosition(x, y);
	text.setFillColor(color);

}

GUI_Quit::GUI_Quit(float x, float y, sf::Color color, int size, sf::Font * font) {

	text = sf::Text("Quit", *font, size);
	text.setPosition(x, y);
	text.setFillColor(color);



}