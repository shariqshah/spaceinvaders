#include "DroneComponent.h"
#include "Entity.h"
#include "BombComponent.h"
#include "EventManager.h"
#include "Level.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Log.h"

#include <stdlib.h>
#include <time.h>
#include <SFML\Graphics.hpp>

using namespace std;

DroneComponent::DroneComponent(Game* game, Entity* entity) : Component(game, entity)
{
	// Register to relevant events
	SubscribeToEvent(EventType::Update, this, &DroneComponent::HandleUpdate);
	SubscribeToEvent(EventType::LevelStart, this, &DroneComponent::HandleLevelStart);

	shootInterval = (rand() % shootIntervalMax) + 6;
}

DroneComponent::~DroneComponent()
{
	UnsubscribeFromEvent(EventType::Update, this);
	UnsubscribeFromEvent(EventType::LevelStart, this);
}

void DroneComponent::HandleUpdate(Object * sender, const map<string, Variant>& eventData)
{
	float currentTime = clock.getElapsedTime().asSeconds();
	int timeElapsed = (int)(currentTime - prevTime);
	
	if(timeElapsed >= shootInterval)
	{
		Entity* bomb = new Entity(game, "Bomb" + to_string(clock.getElapsedTime().asMilliseconds()));
		bomb->AddComponent(new BombComponent(game, bomb, 60.f));

		sf::Sprite* bombSprite = bomb->GetSprite();
		ResourceManager* resourceManager = game->GetResourceManager();
		sf::Texture* bombTexture = resourceManager->GetTexture("Textures/bomb.png");
		bombSprite->setTexture(*bombTexture);

		sf::Vector2f currPos = entity->GetPosition();
		const sf::Texture* droneTex = entity->GetSprite()->getTexture();
		float halfTextureWidth = droneTex->getSize().x / 4.f;
		bomb->SetPosition(currPos.x + halfTextureWidth, entity->GetPositionY());

		Level* level = game->GetLevel();
		level->AddEntity(bomb);
		
		prevTime = currentTime;
	}
}

void DroneComponent::HandleLevelStart(Object * sender, const map<string, Variant>& eventData)
{
	prevTime = clock.getElapsedTime().asSeconds();
}
