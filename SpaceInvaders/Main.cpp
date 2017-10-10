#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <time.h>

#include "Log.h"
#include "Game.h"

float calcDistance(const sf::Vector2f& v1, const sf::Vector2f& v2);

/*
TODO:
- Complete level
- Multiple drone types
- New high score screen
- Animated sprites
- Highscores
x Options
x Barriers
x Sweeper
x Hordes, one horde is killed off, a new one replaces it
x Fix collisions
x Player going out of bounds
- Change menu sound implementation by getting the sf::Sound directly from resource manager so that the playing sf::Sound instance does not get destroyed with the GameState
*/

int main(int argc, const char** argv)
{
	Game game;
	game.Run();

	Log::Message("Game exiting...");

	return 0;
}

float calcDistance(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	sf::Vector2f diff = v2 - v1;
	float distance = sqrtf((diff.x * diff.x) + (diff.y * diff.y));
	return fabsf(distance);
}