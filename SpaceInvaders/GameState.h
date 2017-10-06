#pragma once

#include "Object.h"

class Game;

class GameState : public Object
{
public:
	GameState() {}
	GameState(Game* game);
	~GameState();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
};

