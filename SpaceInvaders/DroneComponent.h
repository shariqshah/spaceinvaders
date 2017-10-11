#pragma once

#include "Component.h"

#include <SFML\System.hpp>

enum class DroneType
{
	MK1,
	MK2,
	MK3
};

class DroneComponent : public Component
{
public:
	
	DroneComponent() {};
	DroneComponent(Game* game, Entity* entity, DroneType type = DroneType::MK1);
	virtual ~DroneComponent();

	virtual ComponentType GetType() override { return ComponentType::Drone; }

	DroneType GetDroneType() { return type; }
private:
	void HandleUpdate(Object* sender, const EventDataMap& eventData);
	void HandleLevelStart(Object* sender, const EventDataMap& eventData);
	void HandleCollision(Object* sender, const EventDataMap& eventData);

	sf::Clock clock;
	const int shootIntervalMax = 30; // maximum number of seconds after which drone drops a bomb
	int shootInterval = 0;
	int health = 10;
	int onHitDamage = 10;
	DroneType type = DroneType::MK1;

};

