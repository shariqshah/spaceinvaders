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

/*
Loads and stores all resource types which include fonts, sounds, music and textures.
Resources are unloaded when the game is closed. All resources are loaded from a data
directory which is specified in the constructor. When providing path to load a resource
the name of the data directory does not need to be included. All paths are assumed relative
to the data directory. 

For example, we want to load a font that is in DataDirectory/Fonts/font_name.ttf, we
only have to provide "Fonts/font_name.ttf" to the resource manager's GetFont function
*/
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
