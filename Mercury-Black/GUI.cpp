#include "GUI.h"

void GUI_Handler::addButton(GUI * button) {
	buttons.push_back(button);
}

void GUI_Handler::draw(sf::RenderWindow * window) {
	for (size_t i = 0; i < buttons.size(); i++)
		buttons[i]->draw(window);
}

void GUI_Handler::isSelected(sf::Vector2f position) {
	for (size_t i = 0; i < buttons.size(); i++)
		buttons[i]->isSelected(position);
}

void GUI_Handler::interact(sf::Vector2f position, GameEngine * engine) {
	for (size_t i = 0; i < buttons.size(); i++)
		if (buttons[i]->isSelected(position))
			buttons[i]->interact(engine);
}

void GUI::interact(GameEngine * engine) {
	(m_funcPtr)(engine);
}