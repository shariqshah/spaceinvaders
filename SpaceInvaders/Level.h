#pragma once

#include "GameState.h"

#include <map>

class Entity;

class Level : public GameState
{
public:
	Level() {};
	Level(Game* game);
	~Level();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	std::map<std::string, Entity*>& GetEntites() { return entities; }

	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	void Initialize();
private:
	std::map<std::string, Entity*> entities;
	std::vector<Entity*> markedEntites;

	void HandlePostUpdate(Object* sender, const EventDataMap& eventData);
};

