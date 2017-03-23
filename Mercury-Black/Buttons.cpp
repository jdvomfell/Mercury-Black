#include "Buttons.h"
#include "Editor.h"
#include "Game.h"
#include "HitboxEditor.h"
#include "MainMenu.h"
#include "HitboxEditor.h"
#include "OptionsMenu.h"
#include "Fade.h"
#include <string>

TextButton::TextButton(std::string name, float x, float y, int size, sf::Font * font, eventFunction funcPtr) {

	text = sf::Text(name, *font, size);
	text.setPosition(x, y);

	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);

	m_funcPtr = funcPtr;
}

bool TextButton::isSelected(sf::Vector2f position) {

	if (text.getGlobalBounds().contains(position)) {

		text.setFillColor(sf::Color::Black);

		return true;

	}

	text.setFillColor(sf::Color(100, 100, 100, 255));

	return false;

}

void TextButton::draw(sf::RenderWindow * window) {

	window->draw(text);

}

IconButton::IconButton(float x, float y, sf::Texture * texture, eventFunction funcPtr) {

	sprite.setTexture(*texture);
	sprite.setPosition(x, y);

	m_funcPtr = funcPtr;

}

bool IconButton::isSelected(sf::Vector2f position) {

	if (sprite.getGlobalBounds().contains(position)) {

		sprite.setColor(sf::Color::Black);

		return true;

	}

	sprite.setColor(sf::Color::White);

	return false;

}

void IconButton::draw(sf::RenderWindow * window) {

	window->draw(sprite);

}

// functions that the function pointer in Button will point to
void changeToGame(GameEngine * engine) {
	engine->changeState(Game::instance(engine));
}
void popState(GameEngine * engine) {
	engine->popState();
}
void changeToEditor(GameEngine * engine) {
	engine->changeState(Editor::instance(engine));
}
void changeToHitboxEditor(GameEngine * engine) {
	engine->changeState(HitboxEditor::instance(engine));
}
void changeToMainMenu(GameEngine * engine) {
	engine->changeState(MainMenu::instance(engine));
}
void changeToOptionsMenu(GameEngine * engine) {
	engine->pushState(OptionsMenu::instance(engine));
}
void changeToKeyBindings(GameEngine * engine) {
	engine->pushState(KeyBind::instance(engine));
}
void quitGame(GameEngine * engine) {
	engine->quit();
}
void doNothing(GameEngine * engine) {
	return;
}