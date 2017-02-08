#ifndef HITBOXEDITOR_H
#define HITBOXEDITOR_H

#include "GameState.h"
#include <SFML\Graphics.hpp>

class HitboxEditor : public GameState {

public:

	GameEngine * engine;

	void init();
	void clean();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);

	static HitboxEditor * instance(GameEngine * engine) { hitboxEditor.engine = engine; return &hitboxEditor; }

	sf::View view;

	sf::Sprite sprite;
	std::string textureID;

protected:

	HitboxEditor() {}

private:

	static HitboxEditor hitboxEditor;

};

#endif