#include "MainMenu.h"
#include "Game.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "Events.h"
#include "Log.h"

using namespace std;

MainMenu::MainMenu(Game* game)
{
	this->game = game;
	ResourceManager* resourceManager = game->GetResourceManager();
	sf::Font* titleFont = resourceManager->GetFont("Fonts/crackman.ttf");
	if(titleFont)
	{
		titleText.setFont(*titleFont);
		titleText.setString("Space Invaders");
		titleText.setCharacterSize(60);
		titleText.setPosition(150.f, 80.f);
	}

	sf::Font* itemFont = resourceManager->GetFont("Fonts/ARCADE.ttf");
	if(itemFont)
	{
		sf::Text playGameText;
		playGameText.setFont(*itemFont);
		playGameText.setCharacterSize(40);
		playGameText.setPosition(300, 280);
		playGameText.setString("Play Game");
		menuItemText.push_back(playGameText);

		sf::Text optionText;
		optionText.setFont(*itemFont);
		optionText.setCharacterSize(40);
		optionText.setPosition(300, 340);
		optionText.setString("Options");
		menuItemText.push_back(optionText);

		sf::Text highScoreText;
		highScoreText.setFont(*itemFont);
		highScoreText.setCharacterSize(40);
		highScoreText.setPosition(300, 400);
		highScoreText.setString("High Score");
		menuItemText.push_back(highScoreText);

		sf::Text quitText;
		quitText.setFont(*itemFont);
		quitText.setCharacterSize(40);
		quitText.setPosition(300, 460);
		quitText.setString("Quit");
		menuItemText.push_back(quitText);
	}

	selectedItem = (int) MenuItems::PlayGame;

	//Setup event handlers
	SubscribeToEvent(EventType::KeyDown, this, &MainMenu::HandleKeyDown);
}

MainMenu::~MainMenu()
{
}

void MainMenu::Update(float deltaTime)
{
}

void MainMenu::Draw()
{
	sf::RenderWindow* window = game->GetWindow();

	window->clear(sf::Color::Black);
	window->draw(titleText);

	//Highlight selected item in blue
	menuItemText[selectedItem].setFillColor(sf::Color::Blue);
	for(const sf::Text& itemText : menuItemText)
	{
		window->draw(itemText);
	}
	menuItemText[selectedItem].setFillColor(sf::Color::White);
}

void MainMenu::HandleKeyDown(Object * sender, const map<string, Variant>& data)
{
	using sf::Keyboard;
	Keyboard::Key key = (Keyboard::Key)data.at("Key").GetInt();

	int currentSelection = selectedItem;
	if(key == Keyboard::Up)
	{
		currentSelection--;
	}
	else if(key == Keyboard::Down)
	{
		currentSelection++;
	}
	else if(key == Keyboard::Return)
	{
		Game::State newState = game->GetCurrentState();
		switch(selectedItem)
		{
		case MenuItems::PlayGame:  newState = Game::State::Level;    break;
		case MenuItems::Options:   newState = Game::State::Options;   break;
		case MenuItems::HighScore: newState = Game::State::HighScore; break;
		case MenuItems::Quit:      newState = Game::State::Quit;      break;
		default: Log::Error("MainMenu:HandleKeyDown", "Invalid menu selection"); break;
		};
		game->SetCurrentState(newState);
	}

	if(currentSelection != selectedItem) // Only do something if up or down are pressed
	{
		selectedItem = currentSelection;
		if(selectedItem < 0) 
			selectedItem = (int)MenuItems::Len - 1;
		else if(selectedItem >= MenuItems::Len)
			selectedItem = 0;
	}
	
}
