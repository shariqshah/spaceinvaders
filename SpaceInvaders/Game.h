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

class Game : public Object
{
public:
	enum class State
	{
		MainMenu = 0,
		Level,
		Options,
		EndGame,
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
	bool IsLevelStarted() const { return isLevelStarted; }
	float GetDeltaTime() { return deltaTime; }
	int GetWindowWidth();
	int GetWindowHeight();
	Level* GetLevel();

private:
	std::vector<GameState*> gameStates;
	sf::RenderWindow* window;
	ResourceManager* resourceManager;
	EventManager* eventManager;

	State currentState;
	bool isLevelStarted = false;
	float deltaTime = 0.16f;
};

