#include "DroneComponent.h"
#include "Entity.h"
#include "BombComponent.h"
#include "SoundComponent.h"
#include "EventManager.h"
#include "Level.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Log.h"

#include <stdlib.h>
#include <time.h>
#include <SFML\Graphics.hpp>

using namespace std;

DroneComponent::DroneComponent(Game* game, Entity* entity, DroneType type) : Component(game, entity), type(type)
{
	sf::Sprite* sprite = entity->GetSprite();
	switch(type)
	{
	case DroneType::MK1:
		health = 10; 
		sprite->setColor(sf::Color::Green);
		break;
	case DroneType::MK2: 
		health = 20;
		sprite->setColor(sf::Color::Yellow);
		break;
	case DroneType::MK3: 
		health = 30; 
		sprite->setColor(sf::Color::Red);
		break;
	};

	// Register to relevant events
	SubscribeToEvent(EventType::Update, this, &DroneComponent::HandleUpdate);
	SubscribeToEvent(EventType::LevelStart, this, &DroneComponent::HandleLevelStart);
	SubscribeToEvent(EventType::Collision, this, &DroneComponent::HandleCollision);

	shootInterval = (rand() % shootIntervalMax) + shootIntervalMin;
}

DroneComponent::~DroneComponent()
{
	UnsubscribeFromEvent(EventType::Update, this);
	UnsubscribeFromEvent(EventType::LevelStart, this);
	UnsubscribeFromEvent(EventType::Collision, this);
}

void DroneComponent::HandleUpdate(Object * sender, const EventDataMap& eventData)
{	
	if(clock.getElapsedTime().asSeconds() >= shootInterval)
	{
		Entity* bomb = new Entity(game, "Bomb" + to_string(clock.getElapsedTime().asMicroseconds()));
		bomb->AddComponent(new BombComponent(game, bomb, 60.f));

		sf::Sprite* bombSprite = bomb->GetSprite();
		ResourceManager* resourceManager = game->GetResourceManager();
		sf::Texture* bombTexture = resourceManager->GetTexture("Textures/bomb.png");
		bombSprite->setTexture(*bombTexture);
		switch(type)
		{
		case DroneType::MK1: bombSprite->setColor(sf::Color::Green); break;
		case DroneType::MK2: bombSprite->setColor(sf::Color::Yellow); break;
		case DroneType::MK3: bombSprite->setColor(sf::Color::Red); break;
		}

		sf::Vector2f currPos = entity->GetPosition();
		const sf::Texture* droneTex = entity->GetSprite()->getTexture();
		float halfTextureWidth = droneTex->getSize().x / 4.f;
		bomb->SetPosition(currPos.x + halfTextureWidth, entity->GetPositionY());

		Level* level = game->GetLevel();
		level->AddEntity(bomb);
		
		clock.restart();

		SoundComponent* soundComponent = (SoundComponent*)entity->GetComponent(ComponentType::Sound);
		if(soundComponent)
		{
			Game::Settings* settings = game->GetSettings();
			if(settings->soundOn)
				soundComponent->Play("Sounds/DroneShoot.wav");
		}
	}
}

void DroneComponent::HandleLevelStart(Object * sender, const EventDataMap& eventData)
{
	clock.restart();
}

void DroneComponent::HandleCollision(Object * sender, const EventDataMap& eventData)
{
	Entity* other = (Entity*)eventData.at("Other").GetVoidPtr();
	if(other->HasComponent(ComponentType::Missile))
	{
		SoundComponent* soundComponent = (SoundComponent*)entity->GetComponent(ComponentType::Sound);
		if(soundComponent)
		{
			Game::Settings* settings = game->GetSettings();
			if(settings->soundOn)
				soundComponent->Play("Sounds/DroneHit.wav");
		}

		health -= onHitDamage;
		if(health <= 0)
		{
			game->GetLevel()->RemoveEntity(entity);
			//Send event that a drone has been destroyed and include the type of drone destroyed as event data
			EventManager* eventManager = game->GetEventManager();
			EventDataMap& eventDataToSend = eventManager->GetEventDataMap();
			eventDataToSend.insert(pair<string, Variant>("DroneType", Variant((int)type)));
			eventManager->SendEvent(EventType::DroneDestroyed, this, eventDataToSend);
		}
	}
}
