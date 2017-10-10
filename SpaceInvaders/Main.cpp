#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <time.h>

#include "Log.h"
#include "Game.h"

float calcDistance(const sf::Vector2f& v1, const sf::Vector2f& v2);

/*
TODO:
- Options
- Barriers
- Complete level
- Sweeper
- Fix collisions
- Player going out pf bounds
- Animated sprites
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