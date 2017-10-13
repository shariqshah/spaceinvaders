#pragma once

#include "GameState.h"

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

/*
Represents Game Over state. Shown when the player dies. Shows the score and then
takes the player back to the main menu
*/
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
	sf::Sound gameOverSound;
	sf::Sound selectSound;
	bool soundPlayed = false;

	void HandleKeyDown(Object* sender, const EventDataMap& eventData);
};

