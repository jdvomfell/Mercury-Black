#include "TextureManager.h"

sf::Texture * TextureManager::getTexture(std::string id) {
	return &textures[id];
}

void TextureManager::loadTexture(std::string id, std::string fileName) {
	sf::Texture texture;

	texture.loadFromFile(fileName);

	textures[id] = texture;
}

void TextureManager::loadAllTextures() {

	/////Player//////

	/* Idle */

	loadTexture("player_idle_1", "Textures/player_idle_1.png");

	/* Run */

	loadTexture("player_run_1", "Textures/player_run_1.png");
	loadTexture("player_run_2", "Textures/player_run_2.png");
	loadTexture("player_run_3", "Textures/player_run_3.png");
	loadTexture("player_run_4", "Textures/player_run_4.png");
	loadTexture("player_run_5", "Textures/player_run_5.png");
	loadTexture("player_run_6", "Textures/player_run_6.png");

	/* Jump */

	loadTexture("player_jump_1", "Textures/player_jump_1.png");
	loadTexture("player_jump_2", "Textures/player_jump_2.png");
	loadTexture("player_jump_3", "Textures/player_jump_3.png");
	loadTexture("player_jump_4", "Textures/player_jump_4.png");
	loadTexture("player_jump_5", "Textures/player_jump_5.png");
	loadTexture("player_jump_6", "Textures/player_jump_6.png");
	loadTexture("player_jump_7", "Textures/player_jump_7.png");
	loadTexture("player_jump_8", "Textures/player_jump_8.png");

}