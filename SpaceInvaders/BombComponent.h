#pragma once

#include "Component.h"

class BombComponent : public Component
{
public:
	BombComponent() {};
	BombComponent(Game* game, Entity* entity, float speed);
	~BombComponent();

	virtual ComponentType GetType() override { return ComponentType::Bomb; }

private:
	void HandleUpdate(Object* sender, const EventDataMap& eventData);
	void HandleCollision(Object* sender, const EventDataMap& eventData);

	float speed = 10.f;
};

