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
	void HandleUpdate(Object* sender, const EventDataMap& eventData);
	void HandleLevelStart(Object* sender, const EventDataMap& eventData);
	void HandleCollision(Object* sender, const EventDataMap& eventData);

	sf::Clock clock;
	const int shootIntervalMax = 20; // maximum number of seconds after which drone drops a bomb
	int shootInterval = 0;
	float prevTime;
};

