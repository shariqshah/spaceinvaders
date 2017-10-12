#include "Log.h"
#include "Game.h"

/*
TODO:
- Fix backspace behaviour in New High Score state
- Missile and bombs apply damage
- Drone bomb damage depends on drone type
- Difficulty related variables in game settings e.g. lives, player speed, drone fire-rate etc
- Color Themes for the whole game, stored in a Theme struct and used in the draw methods?
- Change menu sound implementation by getting the sf::Sound directly from resource manager so that the playing sf::Sound instance does not get destroyed with the GameState
x Animated sprites
x Complete level
x Highscores
x New high score screen
x Multiple drone types
x Options
x Barriers
x Sweeper
x Hordes, one horde is killed off, a new one replaces it
x Fix collisions
x Player going out of bounds
*/

int main(int argc, const char** argv)
{
	Game game;
	game.Run();

	Log::Message("Game exiting...");

	return 0;
}