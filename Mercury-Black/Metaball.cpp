#include "Metaball.h"

#include <chrono>
#include <thread>

const char metaballFragment[] =
"uniform float threshold;"
"uniform sampler2D texture;"
"void main()"
"{"
"    vec4 pixel = gl_Color * texture2D(texture, gl_TexCoord[0].xy);;"
"    if (pixel.a >= threshold) {"
"        pixel.a = 1.0f;"
"        pixel.r = 0.0f;"
"        pixel.g = 0.0f;"
"        pixel.b = 0.0f;"
"    }"
"    else {"
"        discard;"
"    }"
"    gl_FragColor = pixel;"
"}";

const char VertexShader[] =
"uniform sampler2D texture;"
"void main()"
"{"
"gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
"gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
"gl_FrontColor = gl_Color;"
"}";

void MetaballHandler::update(float dt) {

	for (size_t i = 0; i < spawners.size(); i++) {
		spawners[i]->spawn(dt);
	}

	for (size_t i = 0; i < metaballList.size(); i++) {

		metaballList[i]->position += metaballList[i]->velocity;

		metaballList[i]->velocity.y += metaballList[i]->weight;

		if ((metaballList[i]->lifespan -= dt) <= 0)
			removeMetaball(i);

	}

}

void MetaballHandler::draw(sf::RenderWindow * window) {

	metaballAddTexture.clear(sf::Color::Transparent);
	metaballShadedTexture.clear(sf::Color::Transparent);

	for (int i = 0; i < metaballList.size(); i++) {

		if (metaballList[i]->lifespan < DEFAULT_SCALE)
			metaballSprite.setScale(sf::Vector2f(metaballList[i]->lifespan, metaballList[i]->lifespan));
		else
			metaballSprite.setScale(sf::Vector2f(DEFAULT_SCALE, DEFAULT_SCALE));

		metaballSprite.setPosition(metaballList[i]->position);

		metaballAddTexture.draw(metaballSprite, sf::BlendAdd);

	}

	metaballShadedTexture.draw(metaballAddSprite, &shader);

	window->draw(metaballShadedSprite);

}

void MetaballHandler::addSpawner(class MetaballSpawner * metaballSpawner) {

	spawners.push_back(metaballSpawner);

}

void MetaballHandler::addMetaball(sf::Vector2f position, sf::Vector2f velocity, float lifespan, float weight, int spreadX, int spreadY) {

	float xMod = (rand() % spreadX) * 0.10f;
	if (rand() % 2 == 1)
		xMod = -xMod;
	float yMod = (rand() % spreadY) * 0.10f;
	if (rand() % 2 == 1)
		yMod = -yMod;

	Metaball * metaball = new Metaball;

	metaball->position = position;
	metaball->velocity = velocity + sf::Vector2f(xMod, yMod);
	metaball->lifespan = lifespan;
	metaball->weight = weight;

	metaballList.push_back(metaball);

}

void MetaballHandler::sunburst(sf::Vector2f position, int metaballs) {

	for (int i = 0; i < metaballs; i++) {
		addMetaball(position, sf::Vector2f(0, 0), 1.0f, -0.5f, 100, 100);
	}

}

void MetaballHandler::removeMetaball(int i) {

	delete(metaballList[i]);
	metaballList.erase(metaballList.begin() + i);

}

void MetaballHandler::clean() {

	for (size_t i = 0; i < metaballList.size(); i++) {
		delete(metaballList[i]);
	}
	metaballList.clear();
	for (size_t i = 0; i < spawners.size(); i++) {
		delete(spawners[i]);
	}
	spawners.clear();

}

MetaballHandler::MetaballHandler() {

	metaballTexture.loadFromFile("Textures/metaball.png");
	metaballSprite.setTexture(metaballTexture);
	metaballSprite.setOrigin(sf::Vector2f(metaballSprite.getLocalBounds().width / 2, metaballSprite.getLocalBounds().height / 2));
	metaballSprite.setScale(sf::Vector2f(DEFAULT_SCALE, DEFAULT_SCALE));

	if (!sf::Shader::isAvailable()) {
		printf("ERROR: Shaders Not Available\n");
		exit(1);
	}

	if (!shader.loadFromMemory(VertexShader, metaballFragment)) {
		printf("ERROR: Couldn't Load The Metaball Shader\n");
		exit(1);
	}

	renderState.shader = &shader;

	shader.setUniform("threshold", THRESHOLD);

}

void MetaballHandler::init(sf::Vector2u windowSize) {

	metaballAddTexture.create(windowSize.x * 3.5, windowSize.y * 3.5);
	metaballShadedTexture.create(windowSize.x * 3.5, windowSize.y * 3.5);

	metaballAddSprite.setTexture(metaballAddTexture.getTexture());
	metaballShadedSprite.setTexture(metaballShadedTexture.getTexture());

}

MetaballSpawner::MetaballSpawner(MetaballHandler * handler, sf::Vector2f position, sf::Vector2f velocity, float weight, float lifespan, int spawnPerSecond, int spreadX, int spreadY) {

	this->handler = handler;

	this->position = position;
	this->velocity = velocity;
	this->weight = weight;
	this->lifespan = lifespan;
	this->spawnPerSecond = spawnPerSecond;
	this->spreadX = spreadX;
	this->spreadY = spreadY;

}

void MetaballSpawner::spawn(float dt) {

	toSpawn += spawnPerSecond * dt;

	for (int i = 0; i < (int)toSpawn; i++) {
		handler->addMetaball(this->position, this->velocity, this->lifespan, this->weight, this->spreadX, this->spreadY);
		toSpawn--;
	}

}