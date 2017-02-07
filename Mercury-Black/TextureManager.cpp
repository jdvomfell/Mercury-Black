#include "TextureManager.h"

sf::Texture * TextureManager::getTexture(std::string id) {

	if (textures.find(id) == textures.end())
		printf("Error: Could Not Find Texture: %s\n", id.c_str());
	
	return &textures[id];

}

void TextureManager::loadTexture(std::string id, std::string fileName) {
	
	sf::Texture texture;

	if (!texture.loadFromFile(fileName))
		printf("Could Not Load Texture: %s\n", fileName.c_str());

	textures[id] = texture;

}

void TextureManager::loadAllTextures() {

	//////Font///////

	font.loadFromFile("ZenzaiItachi.ttf");
	slideFont.loadFromFile("GOTHIC.TTF");

	/////Player//////

	/* Idle */

	loadTexture("player_idleUnsheathed_1", "Textures/Player/IdleUnsheathed/player_idleUnsheathed_1.png");
	loadTexture("player_idleUnsheathed_2", "Textures/Player/IdleUnsheathed/player_idleUnsheathed_2.png");
	loadTexture("player_idleUnsheathed_3", "Textures/Player/IdleUnsheathed/player_idleUnsheathed_3.png");
	loadTexture("player_idleUnsheathed_4", "Textures/Player/IdleUnsheathed/player_idleUnsheathed_4.png");
	loadTexture("player_idleUnsheathed_5", "Textures/Player/IdleUnsheathed/player_idleUnsheathed_5.png");
	loadTexture("player_idleUnsheathed_6", "Textures/Player/IdleUnsheathed/player_idleUnsheathed_6.png");
	loadTexture("player_idleUnsheathed_7", "Textures/Player/IdleUnsheathed/player_idleUnsheathed_7.png");
	loadTexture("player_idleUnsheathed_8", "Textures/Player/IdleUnsheathed/player_idleUnsheathed_8.png");

	/* Run */

	loadTexture("player_run_1", "Textures/Player/Run/player_run_1.png");
	loadTexture("player_run_2", "Textures/Player/Run/player_run_2.png");
	loadTexture("player_run_3", "Textures/Player/Run/player_run_3.png");
	loadTexture("player_run_4", "Textures/Player/Run/player_run_4.png");
	loadTexture("player_run_5", "Textures/Player/Run/player_run_5.png");
	loadTexture("player_run_6", "Textures/Player/Run/player_run_6.png");

	/* Jump */

	loadTexture("player_jump_1", "Textures/Player/Jump/player_jump_1.png");
	loadTexture("player_jump_2", "Textures/Player/Jump/player_jump_2.png");
	loadTexture("player_jump_3", "Textures/Player/Jump/player_jump_3.png");
	loadTexture("player_jump_4", "Textures/Player/Jump/player_jump_4.png");
	loadTexture("player_jump_5", "Textures/Player/Jump/player_jump_5.png");
	loadTexture("player_jump_6", "Textures/Player/Jump/player_jump_6.png");
	loadTexture("player_jump_7", "Textures/Player/Jump/player_jump_7.png");

	/* In Air */

	loadTexture("player_inAir_1", "Textures/Player/Jump/player_inAir_1.png");
	
	/* Idle Attack */
	loadTexture("player_idleAttack_1", "Textures/Player/Idle-Attack/player_attack_1.png");
	loadTexture("player_idleAttack_2", "Textures/Player/Idle-Attack/player_attack_2.png");
	loadTexture("player_idleAttack_3", "Textures/Player/Idle-Attack/player_attack_3.png");
	loadTexture("player_idleAttack_4", "Textures/Player/Idle-Attack/player_attack_4.png");
	loadTexture("player_idleAttack_5", "Textures/Player/Idle-Attack/player_attack_5.png");
	loadTexture("player_idleAttack_6", "Textures/Player/Idle-Attack/player_attack_6.png");
	loadTexture("player_idleAttack_7", "Textures/Player/Idle-Attack/player_attack_7.png");
	loadTexture("player_idleAttack_8", "Textures/Player/Idle-Attack/player_attack_8.png");
	
	///Ceiling Plant///

	/* Spawn */
	loadTexture("ceilingPlant_spawn_1", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_1.png");
	loadTexture("ceilingPlant_spawn_2", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_2.png");
	loadTexture("ceilingPlant_spawn_3", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_3.png");
	loadTexture("ceilingPlant_spawn_4", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_4.png");
	loadTexture("ceilingPlant_spawn_5", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_5.png");
	loadTexture("ceilingPlant_spawn_6", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_6.png");
	loadTexture("ceilingPlant_spawn_7", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_7.png");
	loadTexture("ceilingPlant_spawn_8", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_8.png");
	loadTexture("ceilingPlant_spawn_9", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_9.png");
	loadTexture("ceilingPlant_spawn_10", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_10.png");
	loadTexture("ceilingPlant_spawn_11", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_11.png");
	loadTexture("ceilingPlant_spawn_12", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_12.png");
	loadTexture("ceilingPlant_spawn_13", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_13.png");
	loadTexture("ceilingPlant_spawn_14", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_14.png");
	loadTexture("ceilingPlant_spawn_15", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_15.png");
	loadTexture("ceilingPlant_spawn_16", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_16.png");
	loadTexture("ceilingPlant_spawn_17", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_17.png");
	loadTexture("ceilingPlant_spawn_18", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_18.png");
	loadTexture("ceilingPlant_spawn_19", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_19.png");
	loadTexture("ceilingPlant_spawn_20", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_20.png");

	/* Idle */

	loadTexture("ceilingPlant_idle_1", "Textures/Enemies/CeilingPlant/Idle/ceilingPlant_Idle_1.png");
	loadTexture("ceilingPlant_idle_2", "Textures/Enemies/CeilingPlant/Idle/ceilingPlant_Idle_2.png");
	loadTexture("ceilingPlant_idle_3", "Textures/Enemies/CeilingPlant/Idle/ceilingPlant_Idle_3.png");
	loadTexture("ceilingPlant_idle_4", "Textures/Enemies/CeilingPlant/Idle/ceilingPlant_Idle_4.png");
	loadTexture("ceilingPlant_idle_5", "Textures/Enemies/CeilingPlant/Idle/ceilingPlant_Idle_5.png");
	loadTexture("ceilingPlant_idle_6", "Textures/Enemies/CeilingPlant/Idle/ceilingPlant_Idle_6.png");
	loadTexture("ceilingPlant_idle_7", "Textures/Enemies/CeilingPlant/Idle/ceilingPlant_Idle_7.png");
	loadTexture("ceilingPlant_idle_8", "Textures/Enemies/CeilingPlant/Idle/ceilingPlant_Idle_8.png");
	loadTexture("ceilingPlant_idle_9", "Textures/Enemies/CeilingPlant/Idle/ceilingPlant_Idle_9.png");
	loadTexture("ceilingPlant_idle_10", "Textures/Enemies/CeilingPlant/Idle/ceilingPlant_Idle_10.png");
	loadTexture("ceilingPlant_idle_11", "Textures/Enemies/CeilingPlant/Idle/ceilingPlant_Idle_11.png");

	/* Triple Attack */

	loadTexture("ceilingPlant_tripleAttack_1", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_1.png");
	loadTexture("ceilingPlant_tripleAttack_2", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_2.png");
	loadTexture("ceilingPlant_tripleAttack_3", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_3.png");
	loadTexture("ceilingPlant_tripleAttack_4", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_4.png");
	loadTexture("ceilingPlant_tripleAttack_5", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_5.png");
	loadTexture("ceilingPlant_tripleAttack_6", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_6.png");
	loadTexture("ceilingPlant_tripleAttack_7", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_7.png");
	loadTexture("ceilingPlant_tripleAttack_8", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_8.png");
	loadTexture("ceilingPlant_tripleAttack_9", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_9.png");
	loadTexture("ceilingPlant_tripleAttack_10", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_10.png");
	loadTexture("ceilingPlant_tripleAttack_11", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_11.png");
	loadTexture("ceilingPlant_tripleAttack_12", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_12.png");
	loadTexture("ceilingPlant_tripleAttack_13", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_13.png");
	loadTexture("ceilingPlant_tripleAttack_14", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_14.png");
	loadTexture("ceilingPlant_tripleAttack_15", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_15.png");
	loadTexture("ceilingPlant_tripleAttack_16", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_16.png");
	loadTexture("ceilingPlant_tripleAttack_17", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_17.png");
	loadTexture("ceilingPlant_tripleAttack_18", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_18.png");
	loadTexture("ceilingPlant_tripleAttack_19", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_19.png");
	loadTexture("ceilingPlant_tripleAttack_20", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_20.png");
	loadTexture("ceilingPlant_tripleAttack_21", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_21.png");
	loadTexture("ceilingPlant_tripleAttack_22", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_22.png");
	loadTexture("ceilingPlant_tripleAttack_23", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_23.png");
	loadTexture("ceilingPlant_tripleAttack_24", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_24.png");
	loadTexture("ceilingPlant_tripleAttack_25", "Textures/Enemies/CeilingPlant/TripleAttack/ceilingPlant_Triple_25.png");
	
	/////PLAY//////

	loadTexture("toriiGate_1", "Textures/Test/ToriiGate1.png");
	loadTexture("toriiGate_2", "Textures/Test/ToriiGate2.png");
	loadTexture("toriiGate_3", "Textures/Test/ToriiGate3.png");
	loadTexture("toriiGate_4", "Textures/Test/ToriiGate4.png");
	loadTexture("toriiGate_5", "Textures/Test/ToriiGate5.png");
	loadTexture("treeTest_1", "Textures/Test/TreeTest1.png");
	loadTexture("Background", "Textures/Test/Background.png");
	loadTexture("tree", "Textures/Test/tree.png");

}