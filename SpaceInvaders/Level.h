#pragma once

#include "GameState.h"

#include <map>
#include <SFML\Graphics.hpp>

class Entity;

class Level : public GameState
{
public:
	Level() {};
	Level(Game* game);
	virtual ~Level();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	std::map<std::string, Entity*>& GetEntites() { return entities; }

	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	void Initialize();
	void SetPlayer(Entity* entity) { playerEntity = entity; };
	Entity* GetPlayer() { return playerEntity; };

private:
	sf::Text scoreText;
	std::map<std::string, Entity*> entities;
	std::vector<Entity*> markedEntites;
	Entity* playerEntity = NULL;
	int numDronesToSpawn = 10;
	int dronesLeft = 10;

	void HandlePostUpdate(Object* sender, const EventDataMap& eventData);
	void HandleDroneDestroyed(Object* sender, const EventDataMap& eventData);
};

