#include "Fade.h"

#include "MainMenu.h"

FadeIn FadeIn::fadein;

void FadeIn::init() {

	fadeColor = sf::Color::Black;
	alpha = 255;

	overlay.setPosition(0, 0);
	overlay.setSize(sf::Vector2f(engine->window.getSize()));
	overlay.setFillColor(sf::Color::Black);

	start = 0;

}

void FadeIn::clean() {

}

void FadeIn::handleEvent() {

	sf::Event event;

	engine->window.pollEvent(event);

	switch (event.type) {

	case sf::Event::Closed:

		engine->quit();

		break;

	}

}

void FadeIn::update(const float dt) {

	if (start == 0) {
		start = 1;
		return;
	}

	if (alpha > 0) {

		if (alpha - dt >= 0)
			alpha -= dt * 75;

		else
			alpha = 0;

	}
	else
		engine->popState();


	fadeColor = sf::Color(0, 0, 0, alpha);
	overlay.setFillColor(fadeColor);

}

void FadeIn::render(const float dt) {

	engine->window.draw(overlay);

}

FadeOut FadeOut::fadeout;

void FadeOut::init() {

	fadeColor = sf::Color::Black;
	alpha = 0;

	overlay.setPosition(0, 0);
	overlay.setSize(sf::Vector2f(engine->window.getSize()));
	overlay.setFillColor(sf::Color::Transparent);

	start = 0;

}

void FadeOut::clean() {

}

void FadeOut::handleEvent() {

	sf::Event event;

	engine->window.pollEvent(event);

	switch (event.type) {

	case sf::Event::Closed:

		engine->quit();

		break;

	}

}

void FadeOut::update(const float dt) {

	if (start == 0) {
		start = 1;
		return;
	}

	if (alpha < 255) {

		if (alpha + dt <= 255)
			alpha += dt * 100;

		else
			alpha = 255;

	}
	else {

		engine->popState();
		engine->changeState(MainMenu::instance(engine));
		engine->pushState(FadeIn::instance(engine));

	}

	fadeColor = sf::Color(0, 0, 0, alpha);
	overlay.setFillColor(fadeColor);

}

void FadeOut::render(const float dt) {

	engine->window.draw(overlay);

}

TransitionState TransitionState::transitionState;

void TransitionState::init() {

	overlay.setPosition(0, 0);
	overlay.setSize(sf::Vector2f(engine->window.getSize().x, engine->window.getSize().y));
	overlay.setFillColor(sf::Color::White);

}

void TransitionState::clean() {

}

void TransitionState::handleEvent() {

	sf::Event event;

	engine->window.pollEvent(event);

	switch (event.type) {

	case sf::Event::Closed:

		engine->quit();

		break;

	}

}

void TransitionState::update(const float dt) {

	engine->popState();

}

void TransitionState::render(const float dt) {

	engine->window.draw(overlay);

}