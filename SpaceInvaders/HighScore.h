#pragma once

#include "GameState.h"

#include <SFML\Graphics.hpp>
/*
Shows the top ten high scores with the names of the players that scored them.
*/
class HighScores : public GameState
{
public:
	HighScores() {};
	HighScores(Game* game);
	virtual ~HighScores();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	sf::Text titleText;
	sf::Text instructionText;
	std::vector<sf::Text> scoreTexts;

	void HandleKeyDown(Object* sender, const EventDataMap& eventData);
};

