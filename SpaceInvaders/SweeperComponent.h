#pragma once

#include "Component.h"

#include <SFML\System.hpp>

/*
Provides sweeper logic. Sweeper shows up after a fixed interval at the top of the screen and if hit by
a missile, provides extra score and lives.
*/
class SweeperComponent : public Component
{
public:
	SweeperComponent() {};
	SweeperComponent(Game* game, Entity* entity);

	virtual ~SweeperComponent();

	virtual ComponentType GetType() override { return ComponentType::Sweeper; }


private:
	sf::Clock clock;
	bool active = false;
	float speed = 100.f;
	int hitScoreReward = 100;
	int hitLifeReward  = 2;

	void HandleUpdate(Object* sender, const EventDataMap& eventData);
	void HandleCollision(Object* sender, const EventDataMap& eventData);
	void HandleLevelStart(Object* sender, const EventDataMap& eventData);
};

