#ifndef FADE_H
#define FADE_H

#include "GameState.h"

class FadeIn : public GameState {

public:

	void init();
	void clean();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);

	static FadeIn * instance(GameEngine * engine) { fadein.engine = engine; return &fadein; }

private:

	GameEngine * engine;
	static FadeIn fadein;

	float alpha;
	sf::Color fadeColor;

	sf::RectangleShape overlay;

	int start;

};

class FadeOut : public GameState {

public:

	void init();
	void clean();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);

	static FadeOut * instance(GameEngine * engine) { fadeout.engine = engine; return &fadeout; }

private:

	GameEngine * engine;
	static FadeOut fadeout;

	float alpha;
	sf::Color fadeColor;

	sf::RectangleShape overlay;

	int start;

};

class TransitionState : public GameState {

public:

	void init();
	void clean();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);

	static TransitionState * instance(GameEngine * engine) { transitionState.engine = engine; return &transitionState; }

private:

	GameEngine * engine;
	static TransitionState transitionState;

	sf::RectangleShape overlay;

};

#endif