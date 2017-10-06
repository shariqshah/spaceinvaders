#pragma once

#include "GameState.h"

#include <SFML\Graphics.hpp>

class HighScore : public GameState
{
public:
	HighScore() {};
	HighScore(Game* game);
	~HighScore();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	sf::Text titleText;
};

