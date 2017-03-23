#include "TextureManager.h"

sf::Texture * TextureManager::getTexture(std::string id) {

	if (textures.find(id) == textures.end()) {
		printf("Error: Could Not Find Texture: %s\n", id.c_str());
		return &textures.begin()->second;
	}
	
	return &textures[id];

}

void TextureManager::loadTexture(std::string id, std::string fileName) {
	
	sf::Texture texture;

	if (!texture.loadFromFile(fileName))
		printf("Could Not Load Texture: %s\n", fileName.c_str());

	textures[id] = texture;

}

void TextureManager::loadTextures(std::string id, std::string sourceLocation, int numTextures) {

	sf::Texture texture;

	std::string fileName;
	std::string idName;

	for (int i = 1; i <= numTextures; i++) {

		fileName = sourceLocation;
		idName = id + "_" + std::to_string(i);

		fileName = fileName + idName + ".png";

		if (!texture.loadFromFile(fileName))
			printf("Could Not Load Texture: %s\n", fileName.c_str());

		textures[idName] = texture;

	}

}

std::string TextureManager::getPrevTextureID(std::string textureID) {

	if (textures.find(textureID) == --textures.end())
		textureID = textures.begin()->first;
	else if (textures.find(textureID) == textures.end())
		textureID = textures.begin()->first;
	else
		textureID = (++textures.find(textureID))->first;

	return textureID;

}

std::string TextureManager::getNextTextureID(std::string textureID) {

	if (textures.find(textureID) == textures.begin())
		textureID = (--textures.end())->first;
	else if (textures.find(textureID) == textures.end())
		textureID = textures.begin()->first;
	else
		textureID = (--textures.find(textureID))->first;

	return textureID;

}

void TextureManager::loadAllTextures() {

	//////Font///////

	font.loadFromFile("ZenzaiItachi.ttf");
	slideFont.loadFromFile("GOTHIC.TTF");

	/////Player//////

	/* Idle */

	loadTextures("player_idleUnsheathed", "Textures/Player/IdleUnsheathed/", 8);

	/* Run */

	loadTextures("player_sheathedRun", "Textures/Player/SheathedRun/", 6);

	/* Jump */
	
	loadTextures("player_jump", "Textures/Player/Jump/", 7);

	/* In Air */

	loadTextures("player_inAir", "Textures/Player/Jump/", 1);
	
	/* Idle Attack */

	loadTextures("player_idleAttack", "Textures/Player/Idle-Attack/", 8);

	/* Roll */

	loadTextures("player_roll", "Textures/Player/Roll/", 5);
	
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

	/* Not Spawned */

	loadTexture("ceilingPlant_notSpawn_1", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_2.png");
	loadTexture("ceilingPlant_notSpawn_2", "Textures/Enemies/CeilingPlant/Spawn/ceilingPlant_Drop_3.png");

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

	loadTexture("spring_background", "Textures/Test/spring_background.png");
	loadTexture("spring_cliff_1", "Textures/Test/spring_cliff_1.png");
	loadTexture("spring_cliff_2", "Textures/Test/spring_cliff_2.png");
	loadTexture("spring_tree_1", "Textures/Test/spring_tree_1.png");
	loadTexture("spring_tree_2", "Textures/Test/spring_tree_2.png");
	loadTexture("spring_log_1", "Textures/Test/spring_log_1.png");
	loadTexture("heart", "Textures/Test/heart.png");

	/////ICONS/////

	loadTexture("boxTool", "Textures/boxTool.png");
	loadTexture("freeTool", "Textures/freeTool.png");
	loadTexture("groundTool", "Textures/groundTool.png");
	loadTexture("eventTool", "Textures/eventTool.png");
	loadTexture("objectTool", "Textures/objectTool.png");
	loadTexture("waterTool", "Textures/waterTool.png");

}