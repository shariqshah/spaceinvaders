#pragma once

#include "GameState.h"

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

/*
Shows the available options that can be tweaked. Sound and music can be toggled on or off.
The keys used to move the player left, right and shoot can be remapped. 
*/
class Options : public GameState
{
public:
	Options() {}
	Options(Game* game);
	virtual ~Options();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
private:
	enum class OptionType
	{
		Sound = 0,
		Music,
		Keys,
		KeyLeft,
		KeyRight,
		KeyShoot,
		Len
	};

	// The key that is currently being remapped, used when re-mapping left, right or shoot key
	enum class SelectedKey
	{
		None = 0,
		Left,
		Right,
		Shoot
	};

	void HandleKeyDown(Object* sender, const EventDataMap& eventData);
	const char* GetKeyName(const sf::Keyboard::Key key);

	sf::Text titleText;
	sf::Text instructionText;
	std::vector<sf::Text> optionTypeTexts;
	sf::Sound moveSound;
	sf::Sound selectSound;

	SelectedKey selectedKey = SelectedKey::None;
	int selectedItem = 0;
};

