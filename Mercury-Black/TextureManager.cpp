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

	loadTextures("player_idle", "Textures/Player/Idle/", 24);

	/* Run */

	loadTextures("player_run", "Textures/Player/Run/", 6);

	/* Jump */
	
	loadTextures("player_jump", "Textures/Player/Jump/", 6);

	/* In Air */

	loadTextures("player_fall", "Textures/Player/Fall/", 3);
	
	/* Idle Attack */

	loadTextures("player_idleAttack", "Textures/Player/Idle-Attack/", 7);

	/* Roll */

	loadTextures("player_roll", "Textures/Player/Roll/", 5);
	
	/* InkAttack */

	loadTextures("player_inkArmAttack", "Textures/Player/Ink-Attack/", 9);

	/* RunAttack */

	loadTextures("player_runAttack", "Textures/Player/Run-Attack/", 6);

	/* JumpAttack */

	loadTextures("player_jumpAttack", "Textures/Player/Jump-Attack/", 6);

	///CorruptPlayer///

	loadTextures("corruptPlayer_idle", "Textures/Enemies/CorruptPlayer/Idle/", 24);

	loadTextures("corruptPlayer_run", "Textures/Enemies/CorruptPlayer/Run/", 6);

	loadTextures("corruptPlayer_idleAttack", "Textures/Enemies/CorruptPlayer/Idle-Attack/", 7);

	///Ceiling Plant///

	/* Drop */

	loadTextures("ceilingPlant_drop", "Textures/Enemies/CeilingPlant/Drop/", 17);

	/* Not Spawned */

	loadTexture("ceilingPlant_notSpawn_1", "Textures/Enemies/CeilingPlant/Drop/ceilingPlant_Drop_2.png");
	loadTexture("ceilingPlant_notSpawn_2", "Textures/Enemies/CeilingPlant/Drop/ceilingPlant_Drop_3.png");

	/* Idle */

	loadTextures("ceilingPlant_idle", "Textures/Enemies/CeilingPlant/Idle/", 12);

	/* Attack */

	loadTextures("ceilingPlant_attack", "Textures/Enemies/CeilingPlant/Attack/", 25);
	
	///Ceiling Plant///

	/* Attack */

	loadTextures("gblob_attack", "Textures/Enemies/GroundBlob/Attack/", 17);

	/* Idle */

	loadTextures("gblob_idle", "Textures/Enemies/GroundBlob/Idle/", 10);

	/* Up */

	loadTextures("gblob_up", "Textures/Enemies/GroundBlob/Up/", 11);

	/* Down */

	loadTextures("gblob_down", "Textures/Enemies/GroundBlob/Down/", 16);

	///Lotus///

	/* Idle */

	loadTextures("lotusMb_idle", "Textures/Enemies/Lotus/Idle/", 10);

	/* Drop-Attack */

	loadTextures("lotusMb_drop", "Textures/Enemies/Lotus/Drop/", 10);

	/* Rise */

	loadTextures("lotusMb_up", "Textures/Enemies/Lotus/Up/", 12);

	/* Ground-Idle */

	loadTextures("lotusMb_gIdle", "Textures/Enemies/Lotus/Ground-Idle/", 5);

	///Spitter///

	/* Attack */

	loadTextures("spitter_SingleAttack", "Textures/Enemies/Spitter/Attack/", 18);

	/////PLAY//////

	loadTexture("spring_background_1", "Textures/Test/spring_background_1.png");
	loadTexture("spring_cliff_1", "Textures/Test/spring_cliff_1.png");
	loadTexture("spring_cliff_2", "Textures/Test/spring_cliff_2.png");
	loadTexture("spring_cliff_3", "Textures/Test/spring_cliff_3.png");
	loadTexture("spring_tree_1", "Textures/Test/spring_tree_1.png");
	loadTexture("spring_tree_2", "Textures/Test/spring_tree_2.png");
	loadTexture("spring_log_1", "Textures/Test/spring_log_1.png");
	loadTexture("heart", "Textures/Test/heart.png");
	loadTexture("spring_ground_1", "Textures/Test/spring_ground_1.png");
	loadTexture("spring_ground_2", "Textures/Test/spring_ground_2.png");
	loadTexture("spring_ground_3", "Textures/Test/spring_ground_3.png");
	loadTexture("spring_ground_4", "Textures/Test/spring_ground_4.png");
	loadTexture("toriiGate_1_back", "Textures/Test/toriiGate_1_back.png");
	loadTexture("toriiGate_1_front", "Textures/Test/toriiGate_1_front.png");
	loadTexture("statue_1", "Textures/Test/statue_1.png");
	loadTexture("bridge_1_back", "Textures/Test/bridge_1_back.png");
	loadTexture("bridge_1_front", "Textures/Test/bridge_1_front.png");
	loadTexture("bridge_2_back", "Textures/Test/bridge_2_back.png");
	loadTexture("bridge_2_front", "Textures/Test/bridge_2_front.png");
	loadTexture("spring_rock_1", "Textures/Test/spring_rock_1.png");
	loadTexture("bamboo_1", "Textures/Test/bamboo_1.png");
	loadTexture("beach_ground_1", "Textures/Test/beach_ground_1.png");
	loadTexture("lily_pad_1", "Textures/Test/Lilly1.png");
	loadTexture("lily_pad_2", "Textures/Test/Lilly2.png");
	loadTexture("swamp_tree_1", "Textures/Test/Tree1.png");
	loadTexture("swamp_tree_2", "Textures/Test/Tree2.png");
	loadTexture("swamp_tree_3", "Textures/Test/Tree3.png");
	loadTexture("swamp_foreground_1", "Textures/Test/MBEnv_Final_FG.png");
	loadTexture("swamp_background_1", "Textures/Test/MBEnv_Final_BG.png");
	loadTexture("swamp_foliage_1", "Textures/Test/Foliage1.png");
	loadTexture("swamp_foliage_2", "Textures/Test/Foliage2.png");

	/////ICONS/////

	loadTexture("boxTool", "Textures/boxTool.png");
	loadTexture("freeTool", "Textures/freeTool.png");
	loadTexture("groundTool", "Textures/groundTool.png");
	loadTexture("eventTool", "Textures/eventTool.png");
	loadTexture("objectTool", "Textures/objectTool.png");
	loadTexture("waterTool", "Textures/waterTool.png");

	printf("LOAD TEXTURE\n");


	/*
	sf::Texture * t = new sf::Texture;
	sf::Clock clock;
	for (int i = 0; i < 100; i++) {
		t->loadFromFile("Textures/Test/tree.png");
	}
	sf::Time elapsed1 = clock.getElapsedTime();
	printf("TEXTURES LOADED %f\n", elapsed1.asSeconds());
	clock.restart();
	printf("Load Texture\n");
	sf::Image s;
	s.loadFromFile("Textures/Test/tree.png");
	for (int i = 0; i < 100; i++) {
		t->loadFromImage(s, sf::IntRect(0, 0, 10, 10));
	}
	elapsed1 = clock.getElapsedTime();
	printf("TEXTURES LOADED %f\n", elapsed1.asSeconds());
	*/
}