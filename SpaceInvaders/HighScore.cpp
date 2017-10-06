#include "HighScore.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Log.h"


HighScore::HighScore(Game* game)
{
	this->game = game;
	ResourceManager* resourceManager = game->GetResourceManager();
	sf::Font* titleFont = resourceManager->GetFont("Fonts/ARCADE.ttf");
	if(titleFont)
	{
		titleText.setFont(*titleFont);
		titleText.setString("High Scores");
		titleText.setCharacterSize(60);
		titleText.setPosition(320.f, 80.f);
	}
}


HighScore::~HighScore()
{
}

void HighScore::Update(float deltaTime)
{
}

void HighScore::Draw()
{
	sf::RenderWindow* window = game->GetWindow();

	window->clear(sf::Color::Black);
	window->draw(titleText);
}
