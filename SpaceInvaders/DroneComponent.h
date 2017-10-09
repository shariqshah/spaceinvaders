#pragma once

#include "Component.h"

#include <SFML\System.hpp>

class DroneComponent : public Component
{
public:
	DroneComponent() {};
	DroneComponent(Game* game, Entity* entity);
	virtual ~DroneComponent();

	virtual ComponentType GetType() override { return ComponentType::Drone; }

private:
	void HandleUpdate(Object* sender, const std::map<std::string, Variant>& eventData);
	void HandleLevelStart(Object* sender, const std::map<std::string, Variant>& eventData);
	void HandleCollision(Object* sender, const std::map<std::string, Variant>& eventData);

	sf::Clock clock;
	const int shootIntervalMax = 20; // maximum number of seconds after which drone drops a bomb
	int shootInterval = 0;
	float prevTime;
};

