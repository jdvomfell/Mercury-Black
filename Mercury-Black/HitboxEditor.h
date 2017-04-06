#ifndef HITBOXEDITOR_H
#define HITBOXEDITOR_H

#include "GameState.h"
#include "Hitbox.h"
#include <SFML\Graphics.hpp>

const enum HitboxSide {
	HITBOXSIDE_TOP,
	HITBOXSIDE_LEFT,
	HITBOXSIDE_RIGHT,
	HITBOXSIDE_BOTTOM
};

class HitboxEditor : public GameState {

public:

	GameEngine * engine;

	void init();
	void clean();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);
	void copy(std::string);
	int parser(std::string, std::string);
	void updateSelectText();

	static HitboxEditor * instance(GameEngine * engine) { hitboxEditor.engine = engine; return &hitboxEditor; }

	sf::View view;

	sf::Sprite sprite;
	std::string textureID;

protected:

	HitboxEditor() {}

private:

	HitboxSide side;
	HitboxMap hitMap;
	Hitbox *hitbox;
	static HitboxEditor hitboxEditor;
	int leftPlacing;
	int chooseCollision;
	HitboxType hitboxType;
	sf::Vector2f initialPosition;
	sf::Vector2f finalPosition;
	sf::RectangleShape drawHitBox;
	sf::RectangleShape spriteBox;

	sf::Text positionText;
	sf::Text sideText;
	sf::Text topText;
	sf::Text leftText;
	sf::Text rightText;
	sf::Text bottomText;

};

#endif