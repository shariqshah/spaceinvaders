#include "Options.h"
#include "Game.h"
#include "ResourceManager.h"

using namespace std;

Options::Options(Game* game) : GameState(game)
{
	ResourceManager* resourceManager = game->GetResourceManager();
	sf::Font* font = resourceManager->GetFont("Fonts/ARCADE.ttf");
	Game::Settings* settings = game->GetSettings();

	if(font)
	{
		titleText.setFont(*font);
		titleText.setString("Options");
		titleText.setCharacterSize(60);
		titleText.setPosition((game->GetWindowWidth() / 2) - (titleText.getLocalBounds().width / 2.f), 80.f);

		string soundString = "Sound On : [";
		if(settings->soundOn)
			soundString += "X]";
		else
			soundString += " ]";
		sf::Text soundText;
		soundText.setFont(*font);
		soundText.setString(soundString);
		soundText.setCharacterSize(25);
		soundText.setPosition(80.f, 150.f);
		optionTypeTexts.push_back(soundText);

		string musicString = "Music On : [";
		if(settings->musicOn)
			musicString += "X]";
		else
			musicString += " ]";
		sf::Text musicText;
		musicText.setFont(*font);
		musicText.setString(musicString);
		musicText.setCharacterSize(25);
		musicText.setPosition(80.f, 200.f);
		optionTypeTexts.push_back(musicText);

		sf::Text keysText;
		keysText.setFont(*font);
		keysText.setString("Keys");
		keysText.setCharacterSize(30);
		keysText.setPosition(80.f, 250.f);
		optionTypeTexts.push_back(keysText);

		sf::Text keyLeftText;
		keyLeftText.setFont(*font);
		keyLeftText.setString("Key Left : [" + string(GetKeyName(settings->left)) + "]");
		keyLeftText.setCharacterSize(25);
		keyLeftText.setPosition(80.f, 300.f);
		optionTypeTexts.push_back(keyLeftText);

		sf::Text keyRightText;
		keyRightText.setFont(*font);
		keyRightText.setString("Key Right : [" + string(GetKeyName(settings->right)) + "]");
		keyRightText.setCharacterSize(25);
		keyRightText.setPosition(80.f, 350.f);
		optionTypeTexts.push_back(keyRightText);

		sf::Text keyShootText;
		keyShootText.setFont(*font);
		keyShootText.setString("Key Shoot : [" + string(GetKeyName(settings->shoot)) + "]");
		keyShootText.setCharacterSize(25);
		keyShootText.setPosition(80.f, 400.f);
		optionTypeTexts.push_back(keyShootText);

		instructionText.setFont(*font);
		instructionText.setString("Use up and down arrows to move selection, Enter to change \nselection and Backspace to go back to main menu.");
		instructionText.setCharacterSize(25);
		instructionText.setPosition((game->GetWindowWidth() / 2) - (instructionText.getLocalBounds().width / 2.f), 480.f);
	}

	sf::SoundBuffer* moveBuffer = game->GetResourceManager()->GetSoundBuffer("Sounds/MenuMove.wav");
	if(moveBuffer)
	{
		moveSound.setBuffer(*moveBuffer);
	}

	sf::SoundBuffer* menuSelectBuffer = game->GetResourceManager()->GetSoundBuffer("Sounds/MenuSelect.wav");
	if(menuSelectBuffer)
	{
		selectSound.setBuffer(*menuSelectBuffer);
	}

	SubscribeToEvent(EventType::KeyDown, this, &Options::HandleKeyDown);
}

Options::~Options()
{
	UnsubscribeFromEvent(EventType::KeyDown, this);
}

void Options::Update(float deltaTime)
{
}

void Options::Draw()
{
	sf::RenderWindow* window = game->GetWindow();

	window->clear(sf::Color::Black);
	window->draw(titleText);

	optionTypeTexts[selectedItem].setFillColor(sf::Color::Blue);
	for(const sf::Text& text : optionTypeTexts)
	{
		window->draw(text);
	}
	optionTypeTexts[selectedItem].setFillColor(sf::Color::White);

	window->draw(instructionText);
}

void Options::HandleKeyDown(Object * sender, const EventDataMap & eventData)
{
	using sf::Keyboard;
	Keyboard::Key key = (Keyboard::Key)eventData.at("Key").GetInt();

	int currentItem = selectedItem;
	Game::Settings* settings = game->GetSettings();

	// Check if we're in key-mapping mode, if we are then we only remap the selected key
	if(selectedKey != SelectedKey::None)
	{
		//If user pressed escape then go back to normal mode
		bool reset = false;
		if(key == Keyboard::Escape)
		{
			reset = true;
		}

		switch(selectedKey)
		{
		case SelectedKey::Left:
		{
			if(!reset) 
				settings->left = key;
			optionTypeTexts[(int)OptionType::KeyLeft].setString("Key Left : [" + string(GetKeyName(settings->left)) + "]");
		}
		break;
		case SelectedKey::Right:
		{
			if(!reset) 
				settings->right = key;
			optionTypeTexts[(int)OptionType::KeyRight].setString("Key Right : [" + string(GetKeyName(settings->right)) + "]");
		}
		break;
		case SelectedKey::Shoot:
		{
			if(!reset) 
				settings->shoot = key;
			optionTypeTexts[(int)OptionType::KeyShoot].setString("Key Shoot : [" + string(GetKeyName(settings->shoot)) + "]");
		}
		break;
		};

		selectedKey = SelectedKey::None;
	}

	if(key == Keyboard::Up)
	{
		currentItem--;
	}
	else if(key == Keyboard::Down)
	{
		currentItem++;
	}
	else if(key == Keyboard::Return)
	{
		switch((OptionType)selectedItem)
		{
		case OptionType::Sound:	   
		{
			settings->soundOn = !settings->soundOn;
			string soundString = "Sound On : [";
			if(settings->soundOn)
				soundString += "X]";
			else
				soundString += " ]";
			optionTypeTexts[(int)OptionType::Sound].setString(soundString);
		}
		break;
		case OptionType::Music:
		{
			settings->musicOn = !settings->musicOn;
			string musicString = "Music On : [";
			if(settings->musicOn)
				musicString += "X]";
			else
				musicString += " ]";
			optionTypeTexts[(int)OptionType::Music].setString(musicString);
		}
		break;
		case OptionType::KeyLeft:  selectedKey = SelectedKey::Left;  		break;
		case OptionType::KeyRight: selectedKey = SelectedKey::Right;  		break;
		case OptionType::KeyShoot: selectedKey = SelectedKey::Shoot;        break;
		};

		// If we entered key mapping mode then change the corresponding text to inform the user
		if(selectedKey != SelectedKey::None)
		{
			switch(selectedKey)
			{
			case SelectedKey::Left:  optionTypeTexts[(int)OptionType::KeyLeft].setString("Key Left : [Press Key any to assign, Esacape to cancel]"); break;
			case SelectedKey::Right: optionTypeTexts[(int)OptionType::KeyRight].setString("Key Right: [Press Key any to assign, Esacape to cancel]"); break;
			case SelectedKey::Shoot: optionTypeTexts[(int)OptionType::KeyShoot].setString("Key Shoot : [Press Key any to assign, Esacape to cancel]"); break;
			};
		}

		selectSound.play();
	}
	else if(key == Keyboard::BackSpace)
	{
		game->SetCurrentState(Game::State::MainMenu);
	}

	if(currentItem != selectedItem)
	{
		selectedItem = currentItem;
		if(selectedItem < 0) 
			selectedItem = (int)OptionType::Len - 1;
		else if(selectedItem >= (int)OptionType::Len)
			selectedItem = 0;
		moveSound.play();
	}
}

const char* Options::GetKeyName(const sf::Keyboard::Key key)
{
	switch(key) 
	{
	default:
	case sf::Keyboard::Unknown:
		return "Unknown";
	case sf::Keyboard::A:
		return "A";
	case sf::Keyboard::B:
		return "B";
	case sf::Keyboard::C:
		return "C";
	case sf::Keyboard::D:
		return "D";
	case sf::Keyboard::E:
		return "E";
	case sf::Keyboard::F:
		return "F";
	case sf::Keyboard::G:
		return "G";
	case sf::Keyboard::H:
		return "H";
	case sf::Keyboard::I:
		return "I";
	case sf::Keyboard::J:
		return "J";
	case sf::Keyboard::K:
		return "K";
	case sf::Keyboard::L:
		return "L";
	case sf::Keyboard::M:
		return "M";
	case sf::Keyboard::N:
		return "N";
	case sf::Keyboard::O:
		return "O";
	case sf::Keyboard::P:
		return "P";
	case sf::Keyboard::Q:
		return "Q";
	case sf::Keyboard::R:
		return "R";
	case sf::Keyboard::S:
		return "S";
	case sf::Keyboard::T:
		return "T";
	case sf::Keyboard::U:
		return "U";
	case sf::Keyboard::V:
		return "V";
	case sf::Keyboard::W:
		return "W";
	case sf::Keyboard::X:
		return "X";
	case sf::Keyboard::Y:
		return "Y";
	case sf::Keyboard::Z:
		return "Z";
	case sf::Keyboard::Num0:
		return "0";
	case sf::Keyboard::Num1:
		return "1";
	case sf::Keyboard::Num2:
		return "2";
	case sf::Keyboard::Num3:
		return "3";
	case sf::Keyboard::Num4:
		return "4";
	case sf::Keyboard::Num5:
		return "5";
	case sf::Keyboard::Num6:
		return "6";
	case sf::Keyboard::Num7:
		return "7";
	case sf::Keyboard::Num8:
		return "8";
	case sf::Keyboard::Num9:
		return "9";
	case sf::Keyboard::Escape:
		return "Escape";
	case sf::Keyboard::LControl:
		return "LControl";
	case sf::Keyboard::LShift:
		return "LShift";
	case sf::Keyboard::LAlt:
		return "LAlt";
	case sf::Keyboard::LSystem:
		return "LSystem";
	case sf::Keyboard::RControl:
		return "RControl";
	case sf::Keyboard::RShift:
		return "RShift";
	case sf::Keyboard::RAlt:
		return "RAlt";
	case sf::Keyboard::RSystem:
		return "RSystem";
	case sf::Keyboard::Menu:
		return "Menu";
	case sf::Keyboard::LBracket:
		return "LBracket";
	case sf::Keyboard::RBracket:
		return "RBracket";
	case sf::Keyboard::SemiColon:
		return "SemiColon";
	case sf::Keyboard::Comma:
		return "Comma";
	case sf::Keyboard::Period:
		return "Period";
	case sf::Keyboard::Quote:
		return "Quote";
	case sf::Keyboard::Slash:
		return "Slash";
	case sf::Keyboard::BackSlash:
		return "BackSlash";
	case sf::Keyboard::Tilde:
		return "Tilde";
	case sf::Keyboard::Equal:
		return "Equal";
	case sf::Keyboard::Dash:
		return "Dash";
	case sf::Keyboard::Space:
		return "Space";
	case sf::Keyboard::Return:
		return "Return";
	case sf::Keyboard::BackSpace:
		return "BackSpace";
	case sf::Keyboard::Tab:
		return "Tab";
	case sf::Keyboard::PageUp:
		return "PageUp";
	case sf::Keyboard::PageDown:
		return "PageDown";
	case sf::Keyboard::End:
		return "End";
	case sf::Keyboard::Home:
		return "Home";
	case sf::Keyboard::Insert:
		return "Insert";
	case sf::Keyboard::Delete:
		return "Delete";
	case sf::Keyboard::Add:
		return "Add";
	case sf::Keyboard::Subtract:
		return "Subtract";
	case sf::Keyboard::Multiply:
		return "Multiply";
	case sf::Keyboard::Divide:
		return "Divide";
	case sf::Keyboard::Left:
		return "Left";
	case sf::Keyboard::Right:
		return "Right";
	case sf::Keyboard::Up:
		return "Up";
	case sf::Keyboard::Down:
		return "Down";
	case sf::Keyboard::Numpad0:
		return "Numpad0";
	case sf::Keyboard::Numpad1:
		return "Numpad1";
	case sf::Keyboard::Numpad2:
		return "Numpad2";
	case sf::Keyboard::Numpad3:
		return "Numpad3";
	case sf::Keyboard::Numpad4:
		return "Numpad4";
	case sf::Keyboard::Numpad5:
		return "Numpad5";
	case sf::Keyboard::Numpad6:
		return "Numpad6";
	case sf::Keyboard::Numpad7:
		return "Numpad7";
	case sf::Keyboard::Numpad8:
		return "Numpad8";
	case sf::Keyboard::Numpad9:
		return "Numpad9";
	case sf::Keyboard::F1:
		return "F1";
	case sf::Keyboard::F2:
		return "F2";
	case sf::Keyboard::F3:
		return "F3";
	case sf::Keyboard::F4:
		return "F4";
	case sf::Keyboard::F5:
		return "F5";
	case sf::Keyboard::F6:
		return "F6";
	case sf::Keyboard::F7:
		return "F7";
	case sf::Keyboard::F8:
		return "F8";
	case sf::Keyboard::F9:
		return "F9";
	case sf::Keyboard::F10:
		return "F10";
	case sf::Keyboard::F11:
		return "F11";
	case sf::Keyboard::F12:
		return "F12";
	case sf::Keyboard::F13:
		return "F13";
	case sf::Keyboard::F14:
		return "F14";
	case sf::Keyboard::F15:
		return "F15";
	case sf::Keyboard::Pause:
		return "Pause";
	}
}