#pragma once

#include "GameState.h"

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class Variant;

class MainMenu : public GameState
{
public:
	MainMenu() {}
	MainMenu(Game* game);
	virtual ~MainMenu();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	enum MenuItems
	{
		PlayGame = 0,
		Options,
		HighScore,
		Quit,
		Len
	};

	sf::Text titleText;
	sf::Sound menuSelectSound;
	sf::Sound menuMoveSound;
	std::vector<sf::Text> menuItemText;
	int selectedItem = 0;

	void HandleKeyDown(Object* sender, const std::map<std::string, Variant>& data);
};

