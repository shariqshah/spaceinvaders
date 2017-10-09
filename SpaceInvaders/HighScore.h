#pragma once

#include "GameState.h"

#include <SFML\Graphics.hpp>

class HighScore : public GameState
{
public:
	HighScore() {};
	HighScore(Game* game);
	virtual ~HighScore();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	sf::Text titleText;
	sf::Text instructionText;

	void HandleKeyDown(Object* sender, const EventDataMap& eventData);
};
