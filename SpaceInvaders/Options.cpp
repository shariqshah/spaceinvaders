#include "Options.h"
#include "Game.h"
#include "ResourceManager.h"

Options::Options(Game* game)
{
	this->game = game;
	ResourceManager* resourceManager = game->GetResourceManager();
	sf::Font* titleFont = resourceManager->GetFont("Fonts/ARCADE.ttf");
	if(titleFont)
	{
		titleText.setFont(*titleFont);
		titleText.setString("Options");
		titleText.setCharacterSize(60);
		titleText.setPosition(360.f, 80.f);
	}
}

Options::~Options()
{
}

void Options::Update(float deltaTime)
{
}

void Options::Draw()
{
	sf::RenderWindow* window = game->GetWindow();

	window->clear(sf::Color::Black);
	window->draw(titleText);
}
