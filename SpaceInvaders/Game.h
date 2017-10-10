#pragma once

#include "Object.h"

#include <vector>
#include <SFML\Window.hpp>

class GameState;
class ResourceManager;
class EventManager;
class Level;

namespace sf
{
	class RenderWindow;
}

#define STARTING_PLAYER_LIVES 30

class Game : public Object
{
public:
	struct PlayerState
	{
		int score = 0;
		int lives = STARTING_PLAYER_LIVES;
	};

	struct Settings
	{
		bool soundOn            = true;
		bool musicOn            = true;
		sf::Keyboard::Key left  = sf::Keyboard::Left;
		sf::Keyboard::Key right = sf::Keyboard::Right;
		sf::Keyboard::Key shoot = sf::Keyboard::Space;
	};

	enum class State
	{
		MainMenu = 0,
		Level,
		Options,
		GameOver,
		HighScore,
		Quit,
		Len
	};

	Game();
	virtual ~Game();

	void Run();
	sf::RenderWindow* GetWindow() { return window; }
	ResourceManager* GetResourceManager() { return resourceManager; }
	EventManager* GetEventManager() { return eventManager; }
	void SetCurrentState(State newState);
	State GetCurrentState() const { return currentState; } 
	bool IsLevelStarted() const { return levelStarted; }
	float GetDeltaTime() { return deltaTime; }
	int GetWindowWidth();
	int GetWindowHeight();
	Level* GetLevel();
	PlayerState* GetPlayerState() { return &playerState; }
	Settings* GetSettings() { return &settings; }

private:
	std::vector<GameState*> gameStates;
	sf::RenderWindow* window;
	ResourceManager* resourceManager;
	EventManager* eventManager;
	Settings settings;

	State currentState;
	State requestedState;
	bool levelStarted = false;
	PlayerState playerState;
	float deltaTime = 0.16f;

	void SetRequestedState();
};

