#include "HealthBar.h"

HealthBar::HealthBar(sf::View * view, int health, int maxHealth) {

	rect.setFillColor(sf::Color::Black);
	rect.setSize(sf::Vector2f(view->getSize().x, view->getSize().y / 100.0f));
	rect.setPosition(view->getCenter().x - (view->getSize().x / 2), view->getCenter().y - (view->getSize().y / 2));

}

void HealthBar::update(sf::View * view, int health, int maxHealth) {

	rect.setSize(sf::Vector2f((view->getSize().x * ((float) health / (float) maxHealth)), (view->getSize().y / 100.0f)));

}

void HealthBar::draw(sf::RenderWindow * window) {

	window->draw(rect);

}