#ifndef METABALL_H
#define METABALL_H

#include<SFML/Graphics.hpp>

#define DEFAULT_SCALE 0.4f
#define THRESHOLD 0.8f

struct Metaball {

	bool dealsDamage;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float lifespan;
	float weight;

};

class MetaballHandler {

public:

	std::vector<class MetaballSpawner *> spawners;
	std::vector<Metaball *> metaballList;

	sf::Texture metaballTexture;
	sf::Sprite metaballSprite;

	sf::RenderTexture metaballAddTexture;
	sf::Sprite metaballAddSprite;

	sf::RenderStates renderState;
	sf::Shader shader;

	MetaballHandler();
	void init(sf::Vector2u windowSize, bool highResolution);

	void addSpawner(class MetaballSpawner * metaballSpawner);
	void addMetaball(sf::Vector2f position, sf::Vector2f velocity, float lifespan, float weight, int spreadX, int spreadY, bool dealsDamage);
	void sunburst(sf::Vector2f positon, int metaballs);

	void update(float dt);
	void draw(sf::RenderWindow * window, sf::View * view);
	void removeMetaball(int i);

	void clean();

};

class MetaballSpawner {

public:

	MetaballHandler * handler;

	sf::Vector2f position;
	sf::Vector2f velocity;

	int spreadX;
	int spreadY;

	float weight;
	float lifespan;

	int spawnPerSecond;
	float toSpawn;

	bool kill;
	bool dealsDamage;

	void spawn(float dt);

	/*
	handler - The handler the metaball spawner will be used through
	position - The position to spawn new metaballs
	velocity - The initial velocity to spawn the metaball with
	weight - The weight will modify the velocity each update
	lifespan - The amount of time the metaball will last in seconds
	spawnPerSecond - how many metaballs will be spawned per second
	spread - the possible spread of the metaballs initial velocity
	(will be divide by 10)
	*/
	MetaballSpawner(MetaballHandler * handler, sf::Vector2f position, sf::Vector2f velocity, float weight, float lifespan, int spawnPerSecond, int spreadX, int spreadY, bool dealsDamage);

};

#endif