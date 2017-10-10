#pragma once

#include "Component.h"

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
	int onHitDamage = 20;
};

