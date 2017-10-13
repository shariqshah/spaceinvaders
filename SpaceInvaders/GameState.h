#pragma once

#include "Object.h"

class Game;

/*
Base GameState that all game states must inherit from. All game states must
implement the Update and Draw methods which are called every frame.
*/
class GameState : public Object
{
public:
	GameState() {}
	GameState(Game* game);
	virtual ~GameState();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
};

