#pragma once

#include "Component.h"

#include <SFML\System.hpp>

enum class DroneType
{
	MK1,
	MK2,
	MK3
};

/*
Provides drone logic. Drones spawn a bomb after a random interval which
is assigned on construction. The interval is between shootMinInterval and shootMaxInterval.
Drones have different types. Other drone types have more health so they are harder to destroy
*/
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
	const int shootIntervalMin = 10;
	int shootInterval = 0;
	int health = 10;
	int onHitDamage = 10;
	DroneType type = DroneType::MK1;

};

