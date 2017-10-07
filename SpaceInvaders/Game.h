#pragma once

#include "Object.h"
#include <vector>

class GameState;
class ResourceManager;
class EventManager;
class Level;

namespace sf
{
	class RenderWindow;
}

#define MAX_PLAYER_LIVES 3

class Game : public Object
{
public:
	struct PlayerState
	{
		int score = 0;
		int lives = MAX_PLAYER_LIVES;
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
	~Game();

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
	PlayerState* GetPlayerState() { return &playerState; };

private:
	std::vector<GameState*> gameStates;
	sf::RenderWindow* window;
	ResourceManager* resourceManager;
	EventManager* eventManager;

	State currentState;
	State requestedState;
	bool levelStarted = false;
	PlayerState playerState;
	float deltaTime = 0.16f;

	void SetRequestedState();
};

