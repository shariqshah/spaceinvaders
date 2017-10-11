#include "NewHighScore.h"
#include "Game.h"
#include "ResourceManager.h"

using namespace std;

NewHighScore::NewHighScore(Game* game) : GameState(game)
{
	ResourceManager* resourceManager = game->GetResourceManager();
	sf::Font* font = resourceManager->GetFont("Fonts/ARCADE.ttf");
	Game::Settings* settings = game->GetSettings();

	if(font)
	{
		titleText.setFont(*font);
		titleText.setString("New High Score");
		titleText.setCharacterSize(60);
		titleText.setPosition((game->GetWindowWidth() / 2) - (titleText.getLocalBounds().width / 2.f), 80.f);

		nameText.setFont(*font);
		nameText.setString("Your Name : ----------");
		nameText.setCharacterSize(40);
		nameText.setPosition((game->GetWindowWidth() / 2) - (nameText.getLocalBounds().width / 2.f), 150.f);

		instructionText.setFont(*font);
		instructionText.setString("Write your name and press Enter to continue");
		instructionText.setCharacterSize(20);
		instructionText.setPosition((game->GetWindowWidth() / 2) - (instructionText.getLocalBounds().width / 2.f), 300.f);
	}

	SubscribeToEvent(EventType::TextEntered, this, &NewHighScore::HandleTextEntered);
	SubscribeToEvent(EventType::KeyDown, this, &NewHighScore::HandleKeyDown);
}

NewHighScore::~NewHighScore()
{
	UnsubscribeFromEvent(EventType::TextEntered, this);
	UnsubscribeFromEvent(EventType::KeyDown, this);
}

void NewHighScore::Update(float deltaTime)
{
}

void NewHighScore::Draw()
{
	sf::RenderWindow* window = game->GetWindow();
	
	window->clear(sf::Color::Black);

	window->draw(titleText);
	window->draw(nameText);
	window->draw(instructionText);
}

void NewHighScore::HandleKeyDown(Object * sender, const EventDataMap & eventData)
{
	using  sf::Keyboard;
	Keyboard::Key key = (Keyboard::Key)eventData.at("Key").GetInt();

	if(key == Keyboard::Return)
	{
		if(enteredText.getSize() == 0)
		{
			enteredText = "Nameless One";
		}
		game->GetPlayerState()->name = enteredText;
		game->AddCurrentPlayerHighscore();
		game->SetCurrentState(Game::State::GameOver);
	}
	else if(key == Keyboard::BackSpace)
	{
		if(enteredText.getSize() > 0)
		{
			//enteredText = enteredText.substring(0, enteredText.getSize()- 1);
			enteredText.erase(enteredText.getSize() - 1);
			nameText.setString("Your Name : " + enteredText);
		}
		
	}
}

void NewHighScore::HandleTextEntered(Object * sender, const EventDataMap & eventData)
{
	uint32_t character = eventData.at("Text").GetUint();

	//enteredText += character;
	enteredText.insert(enteredText.getSize(), character);
	nameText.setString("Your Name : " + enteredText);
}
