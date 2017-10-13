#pragma once

#include "Component.h"

/*
Provides missile logic. Missiles are spawned by the player(Cannon).
Missiles only collide with drones and bombs. When a bomb is hit, it is destroyed.
When a drone is hit, it gets damaged depending on the DroneType
*/
class MissileComponent : public Component
{
public:
	MissileComponent() {};
	MissileComponent(Game* game, Entity* entity, float speed);
	virtual ~MissileComponent();

	virtual ComponentType GetType() override { return ComponentType::Missile; }

private:
	float speed = -80.f;

	void HandleCollision(Object* sender, const EventDataMap& eventData);
	void HandleUpdate(Object* sender, const EventDataMap& eventData);
};

