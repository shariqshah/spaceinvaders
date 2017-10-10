#include "SoundComponent.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Log.h"
#include "Entity.h"

#include <SFML\Audio.hpp>

SoundComponent::SoundComponent(Game * game, Entity * entity) : Component(game, entity)
{
}

SoundComponent::~SoundComponent()
{
	for(auto soundEntry : sounds)
	{
		sf::Sound* sound = soundEntry.second;
		if(sound)
		{
			delete sound;
			sound = NULL;
		}
	}
}

void SoundComponent::AddSound(const std::string & name)
{
	sf::SoundBuffer* buffer = game->GetResourceManager()->GetSoundBuffer(name);
	sf::Sound* sound = new sf::Sound();
	if(buffer)
	{
		sound->setBuffer(*buffer);
		sounds[name] = sound;
	}
	else
	{
		Log::Error("SoundComponent", "Sound '%s' for '%s' not initialized!", name.c_str(), entity->GetName().c_str());
	}
}

void SoundComponent::Play(const std::string & name)
{
	auto soundEntry = sounds.find(name);
	if(soundEntry != sounds.end())
	{
		sf::Sound* sound = soundEntry->second;
		if(sound)
		{
			sound->play();
		}
	}
}

void SoundComponent::PlayDefault()
{
	if(sounds.size() > 0)
	{
		auto soundEntry = sounds.begin();
		sf::Sound* sound = soundEntry->second;
		if(sound)
		{
			sound->play();
		}
	}
}

void SoundComponent::Pause(const std::string & name)
{
	auto soundEntry = sounds.find(name);
	if(soundEntry != sounds.end())
	{
		sf::Sound* sound = soundEntry->second;
		if(sound)
		{
			sound->pause();
		}
	}
}

void SoundComponent::Stop(const std::string & name)
{
	auto soundEntry = sounds.find(name);
	if(soundEntry != sounds.end())
	{
		sf::Sound* sound = soundEntry->second;
		if(sound)
		{
			sound->stop();
		}
	}
}

void SoundComponent::SetLooped(const std::string & name, bool loop)
{
	auto soundEntry = sounds.find(name);
	if(soundEntry != sounds.end())
	{
		sf::Sound* sound = soundEntry->second;
		if(sound)
		{
			sound->setLoop(loop);
		}
	}
}
