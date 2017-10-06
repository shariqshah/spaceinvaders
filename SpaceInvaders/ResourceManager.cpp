#include "ResourceManager.h"
#include "Log.h"

#include <SFML\Graphics.hpp>

ResourceManager::ResourceManager()
{
	dataDirectory = "GameData/";
}

ResourceManager::~ResourceManager()
{
}

sf::Font* ResourceManager::GetFont(const std::string & name)
{
	sf::Font* font = NULL;
	auto it = fonts.find(name);
	if(it != fonts.end())
	{
		font = it->second;
	}
	else
	{
		font = new sf::Font();
		if(!font->loadFromFile(dataDirectory + name))
		{
			Log::Error("ResourceManager:GetFont", "Failed to load font %s", name.c_str());
			delete font;
			return NULL;
		}
		fonts[name] = font;
		Log::Message("Loaded font %s", name.c_str());
	}
	
	return font;
}

sf::Texture * ResourceManager::GetTexture(const std::string & name)
{
	sf::Texture* texture = NULL;
	auto it = textures.find(name);
	if(it != textures.end())
	{
		texture = it->second;
	}
	else
	{
		texture = new sf::Texture();
		if(!texture->loadFromFile(dataDirectory + name))
		{
			Log::Error("ResourceManager:GetTexture", "Failed to load texture %s", name.c_str());
			delete texture;
			return NULL;
		}
		textures[name] = texture;
		Log::Message("Loaded texture %s", name.c_str());
	}

	return texture;
}
