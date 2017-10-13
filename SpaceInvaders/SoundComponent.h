#pragma once

#include "Component.h"

#include <map>

namespace sf
{
	class Sound;
}

/*
Contains sounds that can be played simulatneously. Multiple sounds can be added and then played by their name
*/
class SoundComponent : public Component
{
public:
	SoundComponent() {};
	SoundComponent(Game* game, Entity* entity);
	virtual ~SoundComponent();

	virtual ComponentType GetType() override { return ComponentType::Sound; }

	void AddSound(const std::string& name);
	void Play(const std::string& name);
	void PlayDefault(); // Play the first sound in the sounds list. Used when we know there's only one sound
	void Pause(const std::string& name); 
	void Stop(const std::string& name);
	void SetLooped(const std::string& name, bool loop);
private:
	std::map <std::string, sf::Sound*> sounds;
};

