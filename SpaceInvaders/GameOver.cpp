#include "GameOver.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Log.h"

using namespace std;

GameOver::GameOver(Game* game) : GameState(game)
{
	ResourceManager* resourceManager = game->GetResourceManager();
	sf::Font* font = resourceManager->GetFont("Fonts/ARCADE.ttf");
	if(font)
	{
		messageText.setFont(*font);
		messageText.setString("GAME OVER");
		messageText.setCharacterSize(60);
		messageText.setPosition((game->GetWindowWidth()  / 2.f) - (messageText.getGlobalBounds().width / 2.f), 80.f);

		scoreText.setFont(*font);
		scoreText.setString("Your score : " + to_string(game->GetPlayerState()->score));
		scoreText.setCharacterSize(50);
		scoreText.setPosition((game->GetWindowWidth()  / 2.f) - (scoreText.getGlobalBounds().width / 2.f), game->GetWindowHeight() / 2.f);

		instructionText.setFont(*font);
		instructionText.setString("Press Enter to go back to main menu...");
		instructionText.setCharacterSize(30);
		instructionText.setPosition((game->GetWindowWidth()  / 2.f) - (instructionText.getGlobalBounds().width / 2.f), (game->GetWindowHeight() / 2.f) + 60);
	}

	sf::SoundBuffer* soundBuffer = game->GetResourceManager()->GetSoundBuffer("Sounds/GameOver.wav");
	if(soundBuffer)
	{
		gameOverSound.setBuffer(*soundBuffer);
	}

	sf::SoundBuffer* selectSoundBuffer = game->GetResourceManager()->GetSoundBuffer("Sounds/MenuSelect.wav");
	if(selectSoundBuffer)
	{
		selectSound.setBuffer(*selectSoundBuffer);
	}

	SubscribeToEvent(EventType::KeyDown, this, &GameOver::HandleKeyDown);
}


GameOver::~GameOver()
{
	UnsubscribeFromEvent(EventType::KeyDown, this);
}

void GameOver::Update(float deltaTime)
{
	if(!soundPlayed)
	{
		gameOverSound.play();
		soundPlayed = true;
	}
}

void GameOver::Draw()
{
	sf::RenderWindow* window = game->GetWindow();

	window->clear(sf::Color::Black);
	window->draw(messageText);
	window->draw(scoreText);
	window->draw(instructionText);
}

void GameOver::HandleKeyDown(Object * sender, const EventDataMap & eventData)
{
	using sf::Keyboard;
	Keyboard::Key key = (Keyboard::Key)eventData.at("Key").GetInt();
	Game::PlayerState* playerState = game->GetPlayerState();
	playerState->score = 0;
	playerState->lives = STARTING_PLAYER_LIVES;
	if(key == Keyboard::Return)
	{
		game->SetCurrentState(Game::State::MainMenu);
		selectSound.play();
	}
}
