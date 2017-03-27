/*fndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <map>
#include <string>

class SoundManager {

public: 

	std::map<std::string, sf::Music> music; 
	std::map<std::string, sf::Sound> sounds;

	sf::Music * getMusic(std::string id);
	sf::Music * getMusic(std::string id);

	void loadSong(std::string id, std::string filename);
	void loadSound(std::string id, std::string filename);
	void loadAllSongs();
	void loadAllSounds();

	std::string getPrevSongID(std::string songID);
	std::string getNextSongID(std::string songID);

	std::string getPrevSoundID(std::string soundID);
	std::string getNextSoundID(std::string soundID);
};

#endif 
*/