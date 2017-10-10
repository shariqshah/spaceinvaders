#pragma once

#include "Component.h"

#include <map>

namespace sf
{
	class Sound;
}

class SoundComponent : public Component
{
public:
	SoundComponent() {};
	SoundComponent(Game* game, Entity* entity);
	virtual ~SoundComponent();

	virtual ComponentType GetType() override { return ComponentType::Sound; }

	void AddSound(const std::string& name);
	void Play(const std::string& name);
	void PlayDefault();
	void Pause(const std::string& name); 
	void Stop(const std::string& name);
	void SetLooped(const std::string& name, bool loop);
private:
	std::map <std::string, sf::Sound*> sounds;
};

