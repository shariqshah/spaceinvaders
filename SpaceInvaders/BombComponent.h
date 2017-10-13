#pragma once

#include "Component.h"

/*
Provides bomb logic to an entity. Bombs only damage player and barriers
*/
class BombComponent : public Component
{
public:
	BombComponent() {};
	BombComponent(Game* game, Entity* entity, float speed);
	virtual ~BombComponent();

	virtual ComponentType GetType() override { return ComponentType::Bomb; }

private:
	void HandleUpdate(Object* sender, const EventDataMap& eventData);
	void HandleCollision(Object* sender, const EventDataMap& eventData);

	float speed = 10.f;
};

