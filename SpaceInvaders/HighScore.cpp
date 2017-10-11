#include "HighScore.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Log.h"

using namespace std;

HighScores::HighScores(Game* game) : GameState(game)
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
		instructionText.setString("Press Escape or Backspace to go back to main menu...");
		instructionText.setCharacterSize(20);
		instructionText.setPosition((game->GetWindowWidth()  / 2.f) - (instructionText.getGlobalBounds().width / 2.f), 500);

		int yPos = 180;
		int offset = 40;
		vector<Game::HighScore>& highScores = game->GetHighScores();
		for(Game::HighScore& highScore : highScores)
		{
			sf::Text scoreText;
			scoreText.setFont(*font);
			scoreText.setString(highScore.playerName + "              " + to_string(highScore.score));
			scoreText.setCharacterSize(30);
			scoreText.setPosition((game->GetWindowWidth()  / 2.f) - (scoreText.getGlobalBounds().width / 2.f), yPos);
			scoreTexts.push_back(scoreText);
			yPos += offset;
		}
	}

	SubscribeToEvent(EventType::KeyDown, this, &HighScores::HandleKeyDown);
}


HighScores::~HighScores()
{
	UnsubscribeFromEvent(EventType::KeyDown, this);
}

void HighScores::Update(float deltaTime)
{
}

void HighScores::Draw()
{
	sf::RenderWindow* window = game->GetWindow();

	window->clear(sf::Color::Black);
	window->draw(titleText);

	for(sf::Text& scoreText : scoreTexts)
		window->draw(scoreText);

	window->draw(instructionText);
}

void HighScores::HandleKeyDown(Object * sender, const EventDataMap & eventData)
{
	using sf::Keyboard;
	Keyboard::Key key = (Keyboard::Key)eventData.at("Key").GetInt();
	
	if(key == Keyboard::Escape || key == Keyboard::BackSpace)
	{
		game->SetCurrentState(Game::State::MainMenu);
	}
}
