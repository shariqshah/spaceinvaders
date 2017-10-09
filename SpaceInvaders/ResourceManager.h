#pragma once

#include <string>
#include <map>

namespace sf
{
	class Font;
	class Texture;
	class Sound;
	class SoundBuffer;
	class Music;
}

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	sf::Font*        GetFont(const std::string& name);
	sf::Texture*     GetTexture(const std::string& name);
	sf::SoundBuffer* GetSoundBuffer(const std::string& name);
	sf::Music*       GetMusic(const std::string& name);

private:
	std::map<std::string, sf::Font*> fonts;
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, sf::SoundBuffer*> soundBuffers;
	std::map<std::string, sf::Music*> music;
	std::string dataDirectory;


};
