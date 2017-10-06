#pragma once

#include <string>
#include <map>

namespace sf
{
	class Font;
	class Texture;
}

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	sf::Font* GetFont(const std::string& name);
	sf::Texture* GetTexture(const std::string& name);

private:
	std::map<std::string, sf::Font*> fonts;
	std::map<std::string, sf::Texture*> textures;
	std::string dataDirectory;
};
