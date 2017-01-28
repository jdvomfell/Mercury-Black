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
	
	/* Idle Attack */
	loadTexture("player_idle_attack_1", "Textures/Attack/Idle-Attack/player_attack_1.png");
	loadTexture("player_idle_attack_2", "Textures/Attack/Idle-Attack/player_attack_2.png");
	loadTexture("player_idle_attack_3", "Textures/Attack/Idle-Attack/player_attack_3.png");
	loadTexture("player_idle_attack_4", "Textures/Attack/Idle-Attack/player_attack_4.png");
	loadTexture("player_idle_attack_5", "Textures/Attack/Idle-Attack/player_attack_5.png");
	loadTexture("player_idle_attack_6", "Textures/Attack/Idle-Attack/player_attack_6.png");
	loadTexture("player_idle_attack_7", "Textures/Attack/Idle-Attack/player_attack_7.png");
	loadTexture("player_idle_attack_8", "Textures/Attack/Idle-Attack/player_attack_8.png");
	
	///Ceiling Plant///

	/* Spawn */
	loadTexture("ceilingplant_spawn_1", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_1.png");
	loadTexture("ceilingplant_spawn_2", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_2.png");
	loadTexture("ceilingplant_spawn_3", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_3.png");
	loadTexture("ceilingplant_spawn_4", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_4.png");
	loadTexture("ceilingplant_spawn_5", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_5.png");
	loadTexture("ceilingplant_spawn_6", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_6.png");
	loadTexture("ceilingplant_spawn_7", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_7.png");
	loadTexture("ceilingplant_spawn_8", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_8.png");
	loadTexture("ceilingplant_spawn_9", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_9.png");
	loadTexture("ceilingplant_spawn_10", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_10.png");
	loadTexture("ceilingplant_spawn_11", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_11.png");
	loadTexture("ceilingplant_spawn_12", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_12.png");
	loadTexture("ceilingplant_spawn_13", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_13.png");
	loadTexture("ceilingplant_spawn_14", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_14.png");
	loadTexture("ceilingplant_spawn_15", "Textures/Enemies/CeilingPlant/Spawn/ceilingplant_spawn_15.png");
}