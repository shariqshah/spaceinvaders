#include "Level.h"
#include "Entity.h"
#include "Game.h"
#include "CannonComponent.h"
#include "DroneComponent.h"
#include "SoundComponent.h"
#include "BarrierComponent.h"
#include "SweeperComponent.h"
#include "ResourceManager.h"
#include "Log.h"

#include <assert.h>
#include <SFML\Audio.hpp>

using namespace std;

Level::Level(Game* game)
{
	this->game = game;
	sf::Font* font = game->GetResourceManager()->GetFont("Fonts/ARCADE.ttf");
	if(font)
	{
		scoreText.setFont(*font);
		scoreText.setString("Score : 0");
		scoreText.setPosition((game->GetWindowWidth() / 2) - (scoreText.getLocalBounds().width / 2.f), 10.f);

		livesText.setFont(*font);
		livesText.setString("Lives : " + to_string(game->GetPlayerState()->lives));
		livesText.setPosition(30.f, 10.f);
	}

	music = game->GetResourceManager()->GetMusic("Music/LevelMusic.ogg");
	if(music)
	{
		music->setLoop(true);
		Game::Settings* settings = game->GetSettings();
		if(settings->musicOn)
			music->play();
	}

	SubscribeToEvent(EventType::PostUpdate, this, &Level::HandlePostUpdate);
	SubscribeToEvent(EventType::DroneDestroyed, this, &Level::HandleDroneDestroyed);
}

Level::~Level()
{
	UnsubscribeFromEvent(EventType::PostUpdate, this);
	UnsubscribeFromEvent(EventType::DroneDestroyed, this);

	for(auto entityEntry : entities)
	{
		Entity* entity = entityEntry.second;
		delete entity;
		entity = NULL;
	}

	if(music)
	{
		if(music->getStatus() == sf::Music::Playing)
			music->stop();
	}
}

void Level::Update(float deltaTime)
{
	//Check for collisions
	// This is an extremely naive way of checking for collisions, i.e check every entity against another and inform both.
	// But since there are never that many entites in the level at once, this should suffice
	EventManager* eventManager = game->GetEventManager();
	for(auto entityEntry : entities)
	{
		Entity* entity = entityEntry.second;
		if(entity->IsCheckedForCollisions())
			continue;

		for(auto otherEntityEntry : entities)
		{
			Entity* other = otherEntityEntry.second;
			if(entity == other) // No point in checking collisions with self, carry on
				continue;
			
			//if(other->IsMarkedForDeletion()) // This entity is marked for deletion and won't exist in the next frame. 
			//	continue;                    // For all intents and purposes this entity does not exist so no point in checking for collisions against it
			// So this turned out to be a bad idea :p
				
			if(other->GetSprite()->getGlobalBounds().intersects(entity->GetSprite()->getGlobalBounds()))
			{
				// We have a collision, inform both entities that they are colliding and let them handle 
				// it in whatever way they want
				auto eventData = eventManager->GetEventDataMap();
				eventData.insert(pair<string, Variant>("Other", Variant((void*)other)));
				eventManager->SendEvent(EventType::Collision, this, entity, eventData);
				eventData.erase("Other");

			}
		}
		entity->SetCheckedForCollisions(true);
	}
}

void Level::Draw()
{
	sf::RenderWindow* window = game->GetWindow();
	window->clear(sf::Color::Black);

	window->draw(scoreText);
	window->draw(livesText);

	for(auto entityEntry : entities)
	{
		Entity* entity = entityEntry.second;
		sf::Sprite* sprite = entity->GetSprite();
		window->draw(*sprite);
	}
}

void Level::AddEntity(Entity * entity)
{
	assert(entity);

	auto ret = entities.insert(pair<string, Entity*>(entity->GetName(), entity));
	if(ret.second)
	{
		Log::Message("'%s' added to the level", entity->GetName().c_str());
	}
	else
	{
		Log::Error("Level:AddEntity", "Failed to add '%s' to the level", entity->GetName().c_str());
	}
}

void Level::RemoveEntity(Entity* entity)
{
	if(!entity->IsMarkedForDeletion())
	{
		entity->SetMarkedForDeletion(true);
		markedEntites.push_back(entity);
	}
}

void Level::Initialize()
{
	//TODO: Maybe load level info from a file?
	Entity* player = new Entity(game, "Player");
	player->AddComponent(new CannonComponent(game, player, 100.f));
	sf::Texture* texture = game->GetResourceManager()->GetTexture("Textures/cannon.png");
	sf::Sprite* playerSprite = player->GetSprite();
	playerSprite->setTexture(*texture);
	player->SetPosition(game->GetWindowWidth() / 2, game->GetWindowHeight() - 150);

	SoundComponent* soundComponent = (SoundComponent*)player->AddComponent(new SoundComponent(game, player));
	soundComponent->AddSound("Sounds/CannonShoot.wav");
	soundComponent->AddSound("Sounds/CannonHit.wav");

	AddEntity(player);
	SetPlayer(player);

	//Add Ground
	Entity* ground = new Entity(game, "Ground");
	sf::RenderWindow* window = game->GetWindow();
	ground->SetPosition(0.f, window->getSize().y - 50.f);
	sf::Sprite* groundSprite = ground->GetSprite();
	sf::Texture* groundTexture = game->GetResourceManager()->GetTexture("Textures/cannon.png");
	groundSprite->setTexture(*groundTexture);
	groundTexture->setRepeated(true);
	groundSprite->setTextureRect(sf::IntRect(0, 0, window->getSize().x, 64));
	AddEntity(ground);

	//Add Barriers
	int numBarriers = 5;
	float barrierGap = 150.f;
	sf::Texture* barrierTexture = game->GetResourceManager()->GetTexture("Textures/barrier.png");
	for(int i = 0; i < numBarriers; i++)
	{
		Entity* barrier = new Entity(game, "Barrier" + to_string(i + 1));
		barrier->AddComponent(new BarrierComponent(game, barrier, 100));
		sf::Sprite* barrierSprite = barrier->GetSprite();
		barrierSprite->setTexture(*barrierTexture);
		//barrierSprite->setTextureRect(sf::IntRect(0, 0, barrierSprite->getGlobalBounds().width, barrierSprite->getGlobalBounds().height));
		barrier->SetPosition(marginX + (barrierTexture->getSize().x + barrierGap * i), game->GetWindowHeight() - 200);

		SoundComponent* barrierSoundComponent = (SoundComponent*)barrier->AddComponent(new SoundComponent(game, barrier));
		barrierSoundComponent->AddSound("Sounds/BarrierHit.wav");
		AddEntity(barrier);
	}

	//Add Sweeper
	Entity* sweeper = new Entity(game, "Sweeper");
	sweeper->AddComponent(new SweeperComponent(game, sweeper));
	sf::Texture* sweeperTexture = game->GetResourceManager()->GetTexture("Textures/sweeper.png");
	sf::Sprite* sweeperSprite = sweeper->GetSprite();
	sweeperSprite->setTexture(*sweeperTexture);

	SoundComponent* sweeperSoundComponent = (SoundComponent*)sweeper->AddComponent(new SoundComponent(game, sweeper));
	sweeperSoundComponent->AddSound("Sounds/SweeperMove.wav");
	sweeperSoundComponent->SetLooped("Sounds/SweeperSound.wav", true);

	sweeperSoundComponent->AddSound("Sounds/SweeperHit.wav");

	AddEntity(sweeper);

	//Spawn the first drone horde
	hordeNum = 1;
	SpawnHorde();
}

void Level::UpdatePlayerStatsText()
{
	livesText.setString("Lives : " + to_string(game->GetPlayerState()->lives));
	scoreText.setString("Score : " + to_string(game->GetPlayerState()->score));
}

void Level::HandlePostUpdate(Object * sender, const EventDataMap & eventData)
{
	//Remove all entities marked for deletion
	for(Entity* entity : markedEntites)
	{
		if(!entity) 
			continue;

		string entityName = entity->GetName();
		auto iter = entities.find(entityName);
		if(iter != entities.end())
		{
			entities.erase(iter);
			delete entity;
			entity = NULL;
			Log::Message("Removed entity '%s' from level", entityName.c_str());
		}
		else
		{
			Log::Error("Level:HandlePostUpdate", "Failed to remove entity '%s' from the level", entityName.c_str());
		}
	}
	markedEntites.clear();

	// Clear all entities' checked for collision flag for the next frame
	for(auto entityEntry : entities)
	{
		Entity* entity = entityEntry.second;
		entity->SetCheckedForCollisions(false);
	}
}

void Level::HandleDroneDestroyed(Object * sender, const EventDataMap & eventData)
{
	game->GetPlayerState()->score += 10;
	scoreText.setString("Score : " + to_string(game->GetPlayerState()->score));
	scoreText.setPosition((game->GetWindowWidth() / 2) - (scoreText.getLocalBounds().width / 2.f), 10.f);
	dronesLeft--;
	Log::Message("Drones left : %d", dronesLeft);

	if(dronesLeft == 0)
	{
		// Level cleared, spawn new, more difficult horde
		hordeNum++;
		SpawnHorde();
		//game->SetCurrentState(Game::State::GameOver);
	}
}

void Level::SpawnHorde()
{
	// Add Drones
	sf::Texture* droneTexture = game->GetResourceManager()->GetTexture("Textures/drone.png");
	dronesLeft = 0;
	int numRows = 5, numColumns = 18;
	float gapX = 20, gapY = 60.f;
	for(int i = 0; i < numRows; i++)
	{
		for(int j = 0; j < numColumns; j++)
		{
			Entity* drone = new Entity(game, "Drone" + to_string(dronesLeft + 1));
			drone->AddComponent(new DroneComponent(game, drone));
			sf::Sprite* droneSprite = drone->GetSprite();
			droneSprite->setTexture(*droneTexture);
			drone->SetPosition((marginX * 2.5f) + (droneTexture->getSize().x * j) + (j * gapX), marginY + (i * gapY));

			SoundComponent* droneSoundComponent = (SoundComponent*)drone->AddComponent(new SoundComponent(game, drone));
			droneSoundComponent->AddSound("Sounds/DroneShoot.wav");
			droneSoundComponent->AddSound("Sounds/DroneHit.wav");

			AddEntity(drone);
			dronesLeft++;
		}
	}
}
