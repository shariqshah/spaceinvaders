#pragma once

#include "GameState.h"

#include <map>
#include <SFML\Graphics.hpp>

namespace sf
{
	class Music;
}

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
	void UpdateLivesText();
	void SetPlayer(Entity* entity) { playerEntity = entity; };
	Entity* GetPlayer() { return playerEntity; };
	int GetMarginX() { return marginX; }
	int GetMarginY() { return marginY; }

private:
	sf::Text scoreText;
	sf::Text livesText;
	sf::Music* music = NULL;

	std::map<std::string, Entity*> entities;
	std::vector<Entity*> markedEntites;
	Entity* playerEntity = NULL;
	int numDronesToSpawn = 10;
	int dronesLeft = 10;
	int marginX = 20;
	int marginY = 90;

	void HandlePostUpdate(Object* sender, const EventDataMap& eventData);
	void HandleDroneDestroyed(Object* sender, const EventDataMap& eventData);
};

