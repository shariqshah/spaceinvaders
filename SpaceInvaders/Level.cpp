#include "Level.h"
#include "Entity.h"
#include "Game.h"
#include "CannonComponent.h"
#include "DroneComponent.h"
#include "ResourceManager.h"
#include "Log.h"

#include <assert.h>

using namespace std;

Level::Level(Game* game)
{
	this->game = game;

	SubscribeToEvent(EventType::PostUpdate, this, &Level::HandlePostUpdate);
}

Level::~Level()
{
	UnsubscribeFromEvent(EventType::PostUpdate, this);
	for(auto entityEntry : entities)
	{
		Entity* entity = entityEntry.second;
		delete entity;
		entity = NULL;
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
	player->AddComponent(new CannonComponent(game, player, 1000.f));
	sf::Texture* texture = game->GetResourceManager()->GetTexture("Textures/cannon.png");
	sf::Sprite* playerSprite = player->GetSprite();
	playerSprite->setTexture(*texture);
	player->SetPosition(game->GetWindowWidth() / 2, game->GetWindowHeight() - 100);
	AddEntity(player);

	// Add Drones
	int numDrones = 1;
	sf::Texture* droneTexture = game->GetResourceManager()->GetTexture("Textures/drone.png");
	for(int i = 0; i < numDrones; i++)
	{
		Entity* drone = new Entity(game, "Drone" + to_string(i + 1));
		drone->AddComponent(new DroneComponent(game, drone));
		sf::Sprite* droneSprite = drone->GetSprite();
		droneSprite->setTexture(*droneTexture);
		drone->SetPosition(droneTexture->getSize().x * i, 300.f);
		AddEntity(drone);
	}

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
