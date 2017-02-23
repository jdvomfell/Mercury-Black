#include "Buttons.h"
#include "Editor.h"
#include "Game.h"
#include "HitboxEditor.h"
#include "Fade.h"
#include <string>

Button::Button(std::string name, float x, float y, sf::Color color, int size, sf::Font * font, eventFunction funcPtr){

	text = sf::Text(name, *font, size);
	text.setPosition(x, y);
	text.setFillColor(color);

	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	
	 m_funcPtr = funcPtr;
}

void Button::interact(GameEngine * engine) {
	(m_funcPtr)(engine);
}

void changeToGame(GameEngine * engine) {
	engine->changeState(Game::instance(engine));
}
void changeToEditor(GameEngine * engine) {
	engine->changeState(Editor::instance(engine));
}
void changeToHitboxEditor(GameEngine * engine) {
	engine->changeState(HitboxEditor::instance(engine));
}
void quitGame(GameEngine * engine) {
	engine->quit();
}
void doNothing(GameEngine * engine) {
	return;
}