#pragma once

#include "Component.h"

/*
Provides barrier logic when added to an entity, expects an entity to have an
animation component which is used to represent the damage state of the barrier.
*/
class BarrierComponent : public Component
{
public:
	BarrierComponent() {};
	BarrierComponent(Game* game, Entity* entity, int startingHealth);

	virtual ~BarrierComponent();

	virtual ComponentType GetType() override { return ComponentType::Barrier; }

private:
	void HandleCollision(Object* sender, const EventDataMap& eventData);

	int health = 100;
	int onHitDamage = 10;
};

