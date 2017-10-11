#pragma once

#include "GameState.h"

#include <SFML\Graphics.hpp>

class NewHighScore : public GameState
{
public:
	NewHighScore() {};
	NewHighScore(Game* game);
	virtual ~NewHighScore();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:

	void HandleKeyDown(Object* sender, const EventDataMap& eventData);
	void HandleTextEntered(Object* sender, const EventDataMap& eventData);
	sf::String enteredText = "";

	sf::Text titleText;
	sf::Text nameText;
	sf::Text instructionText;
};

