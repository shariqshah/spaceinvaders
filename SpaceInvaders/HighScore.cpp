#include "HighScore.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Log.h"


HighScore::HighScore(Game* game) : GameState(game)
{
	ResourceManager* resourceManager = game->GetResourceManager();
	sf::Font* font = resourceManager->GetFont("Fonts/ARCADE.ttf");
	if(font)
	{
		titleText.setFont(*font);
		titleText.setString("High Scores");
		titleText.setCharacterSize(60);
		titleText.setPosition((game->GetWindowWidth()  / 2.f) - (titleText.getGlobalBounds().width / 2.f), 80.f);

		instructionText.setFont(*font);
		instructionText.setString("Press Enter to go back to main menu...");
		instructionText.setCharacterSize(30);
		instructionText.setPosition((game->GetWindowWidth()  / 2.f) - (instructionText.getGlobalBounds().width / 2.f), (game->GetWindowHeight() / 2.f) + 60);
	}

	SubscribeToEvent(EventType::KeyDown, this, &HighScore::HandleKeyDown);
}


HighScore::~HighScore()
{
	UnsubscribeFromEvent(EventType::KeyDown, this);
}

void HighScore::Update(float deltaTime)
{
}

void HighScore::Draw()
{
	sf::RenderWindow* window = game->GetWindow();

	window->clear(sf::Color::Black);
	window->draw(titleText);
	window->draw(instructionText);
}

void HighScore::HandleKeyDown(Object * sender, const EventDataMap & eventData)
{
	using sf::Keyboard;
	Keyboard::Key key = (Keyboard::Key)eventData.at("Key").GetInt();
	
	if(key == Keyboard::Return)
	{
		game->SetCurrentState(Game::State::MainMenu);
	}
}
