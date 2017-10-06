#pragma once

#include "GameState.h"

#include <SFML\Graphics.hpp>

class Options : public GameState
{
public:
	Options() {}
	Options(Game* game);
	~Options();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
private:
	sf::Text titleText;
};

