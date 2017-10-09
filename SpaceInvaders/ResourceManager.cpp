#include "ResourceManager.h"
#include "Log.h"

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

ResourceManager::ResourceManager()
{
	dataDirectory = "GameData/";
}

ResourceManager::~ResourceManager()
{
	for(auto fontEntry : fonts)
	{
		sf::Font* font = fontEntry.second;
		if(font)
			delete font;
	}

	for(auto textureEntry : textures)
	{
		sf::Texture* texture = textureEntry.second;
		if(texture)
			delete texture;
	}

	for(auto soundBufferEntry : soundBuffers)
	{
		sf::SoundBuffer* soundBuffer = soundBufferEntry.second;
		if(soundBuffer)
			delete soundBuffer;
	}

	for(auto musicFileEntry : music)
	{
		sf::Music* music = musicFileEntry.second;
		if(music)
			delete music;
	}
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

sf::SoundBuffer * ResourceManager::GetSoundBuffer(const std::string & name)
{
	sf::SoundBuffer* soundBuffer = NULL;
	auto it = soundBuffers.find(name);
	if(it != soundBuffers.end())
	{
		soundBuffer = it->second;
	}
	else
	{
		soundBuffer = new sf::SoundBuffer();
		if(!soundBuffer->loadFromFile(dataDirectory + name))
		{
			Log::Error("ResourceManager:GetSoundBuffer", "Failed to load sound buffer %s", name.c_str());
			delete soundBuffer;
			return NULL;
		}
		soundBuffers[name] = soundBuffer;
		Log::Message("Created sound buffer from %s", name.c_str());
	}

	return soundBuffer;
}

sf::Music * ResourceManager::GetMusic(const std::string & name)
{
	sf::Music* musicFile = NULL;
	auto it = music.find(name);
	if(it != music.end())
	{
		musicFile = it->second;
	}
	else
	{
		musicFile = new sf::Music();
		if(!musicFile->openFromFile(dataDirectory + name))
		{
			Log::Error("ResourceManager:GetMusic", "Failed to load music file %s", name.c_str());
			delete musicFile;
			return NULL;
		}
		music[name] = musicFile;
		Log::Message("Loaded music file from %s", name.c_str());
	}

	return musicFile;
}
