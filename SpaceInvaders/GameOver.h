#pragma once

#include "GameState.h"

#include <SFML\Graphics.hpp>

class GameOver : public GameState
{
public:
	GameOver() {};
	GameOver(Game* game);
	virtual ~GameOver();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	sf::Text messageText;
	sf::Text scoreText;
	sf::Text instructionText;

	void HandleKeyDown(Object* sender, const EventDataMap& eventData);
};

