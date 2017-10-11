#include "Game.h"
#include "Log.h"
#include "MainMenu.h"
#include "Options.h"
#include "HighScore.h"
#include "NewHighScore.h"
#include "Level.h"
#include "GameOver.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "Events.h"

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

Game::Game()
{
	game = this;

	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Invaders", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(60);
	Log::Message("Window created");

	// Create sub-systems
	resourceManager = new ResourceManager();
	eventManager = new EventManager();

	// Create all game states
	gameStates.resize((int)State::Len);
	gameStates[(int)State::MainMenu]  = new MainMenu(this);

	currentState = State::MainMenu;
	requestedState = currentState;

	//Seed the random number generator
	srand(time(NULL));
}

Game::~Game()
{
	for(GameState* state : gameStates)
	{
		if(state) delete state;
	}

	if(window) delete window;
	if(resourceManager) delete resourceManager;
	if(eventManager) delete eventManager;
}

void Game::Run()
{
	sf::Clock clock;
	float prevTime = clock.getElapsedTime().asSeconds();
	while(window->isOpen())
	{
		sf::Event event;
		while(window->pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window->close();
			}
			else if(event.type == sf::Event::KeyPressed)
			{
				auto eventData = eventManager->GetEventDataMap();

				eventData.insert(pair<string, Variant>("Key", Variant((int)event.key.code)));
				eventData.insert(pair<string, Variant>("Control", Variant(event.key.control)));
				eventData.insert(pair<string, Variant>("Shift", Variant(event.key.shift)));
				eventManager->SendEvent(EventType::KeyDown, this, eventData);

				/*if(event.key.code == sf::Keyboard::Escape)
				{
					window->close();
				}*/	
			}
			else if(event.type == sf::Event::KeyReleased)
			{
				auto eventData = eventManager->GetEventDataMap();

				eventData.insert(pair<string, Variant>("Key", Variant((int)event.key.code)));
				eventData.insert(pair<string, Variant>("Control", Variant(event.key.control)));
				eventData.insert(pair<string, Variant>("Shift", Variant(event.key.shift)));
				eventManager->SendEvent(EventType::KeyUp, this, eventData);
			}
			else if(event.type == sf::Event::TextEntered)
			{
				if(event.text.unicode < 128) // We're only handling ascii characters here
				{
					auto eventData = eventManager->GetEventDataMap();
					eventData.insert(pair<string, Variant>("Text", Variant((uint32_t)event.text.unicode)));
					eventManager->SendEvent(EventType::TextEntered, this, eventData);
				}
			}
		}

		float currentTime = (float)clock.getElapsedTime().asSeconds();
		deltaTime = currentTime - prevTime;
		prevTime = currentTime;

		if(gameStates[(int)currentState])
		{
			auto eventData = eventManager->GetEventDataMap();
			//Send Update Event
			eventData.insert(pair<string, Variant>("DeltaTime", Variant(deltaTime)));
			eventManager->SendEvent(EventType::Update, this, eventData);
			
			//Update Current GameState
			gameStates[(int)currentState]->Update(deltaTime);

			//Send Post-Update Event
			eventManager->SendEvent(EventType::PostUpdate, this, eventData);

			// Draw
			gameStates[(int)currentState]->Draw();
		}
		else
		{
			Log::Message("State Unimplemented!");
		}

		window->display();

		eventManager->ResetEventDataMap();

		if(currentState != requestedState)
		{
			SetRequestedState();
		}
	}
}

void Game::SetRequestedState()
{
	if(requestedState == currentState)
		return;

	switch(requestedState)
	{
	case State::Level:
	{
		gameStates[(int)State::Level] = new Level(this);
		Level* level = static_cast<Level*>(gameStates[(int)State::Level]);
		level->Initialize();
		levelStarted = true;
		// Send a Level started event
		eventManager->SendEvent(EventType::LevelStart);
	}
	break;
	case State::HighScore:
	{
		levelStarted = false;
		gameStates[(int)Game::State::HighScore] = new HighScores(this);
	}
	break;
	case State::GameOver:
	{
		gameStates[(int)Game::State::GameOver] = new GameOver(this);
		levelStarted = false;
	}
	break;
	case State::MainMenu:
	{
		gameStates[(int)Game::State::MainMenu] = new MainMenu(this);
	}
	break;
	case State::Options:
	{
		gameStates[(int)Game::State::Options] = new Options(this);
	}
	break;
	case State::NewHighScore:
	{
		gameStates[(int)Game::State::NewHighScore] = new NewHighScore(this);
	}
	break;
	};

	currentState = requestedState;

	for(int i = 0; i < gameStates.size(); i++)
	{
		if(i == (int)currentState)
			continue;

		if(gameStates[i])
		{
			delete gameStates[i];
			gameStates[i] = NULL;
		}
	}
}


void Game::SetCurrentState(State newState)
{
	if(newState == State::Quit)
	{
		window->close();
		return;
	}
	else if(newState == State::GameOver && currentState != State::NewHighScore) // Check if the current score is a new highscore, if it is, then go to new high score screen
	{
		int minScore = 0;
		if(highScores.size() > 0) minScore = highScores[0].score;

		for(HighScore& highScore : highScores)
		{
			if(highScore.score < minScore)
				minScore = highScore.score;
		}

		if(playerState.score > minScore)
		{
			if(highScores.size() >= MAX_HIGHSCORES)
			{
				highScores.pop_back();
			}
			newState = State::NewHighScore;
		}
	}

	requestedState = newState;
}

int Game::GetWindowWidth()
{
	return (int)window->getSize().x;
}

int Game::GetWindowHeight()
{
	return (int)window->getSize().y;
}

Level * Game::GetLevel()
{
	return static_cast<Level*>(gameStates[(int)State::Level]);
}

void Game::AddCurrentPlayerHighscore()
{
	HighScore score;
	score.playerName = playerState.name;
	score.score = playerState.score;
	highScores.push_back(score);

	// Sort the highscores by highest score
	if(highScores.size() > 1)
	{
		sort(highScores.begin(), highScores.end(), [](HighScore& a, HighScore&b)
		{
			return b.score < a.score;
		});
	}
}

void Game::ResetPlayerState()
{
	playerState.score = 0;
	playerState.lives = STARTING_PLAYER_LIVES;
}
