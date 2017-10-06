#pragma once

#include "Component.h"

class MissileComponent : public Component
{
public:
	MissileComponent() {};
	MissileComponent(Game* game, Entity* entity, float speed);
	~MissileComponent();

	virtual ComponentType GetType() override { return ComponentType::Missile; }

private:
	float speed = -80.f;

	void HandleCollision(Object* sender, const EventDataMap& eventData);
	void HandleUpdate(Object* sender, const EventDataMap& eventData);
};

