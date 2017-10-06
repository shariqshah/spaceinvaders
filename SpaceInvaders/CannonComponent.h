#pragma once

#include "Component.h"
#include <SFML\System.hpp>

// Cannon component gets input from user and moves around, shoots
// and on collision with bomb sends event which reduces player's life

class CannonComponent :	public Component
{
public:
	CannonComponent() {};
	CannonComponent(Game* game, Entity* entity, float speed);
	~CannonComponent();

	virtual ComponentType GetType() override { return ComponentType::Cannon; }

private:
	void HandleKeyDown(Object* sender, const EventDataMap& eventData);

	float moveSpeed = 5.f;
	sf::Clock clock;
};

