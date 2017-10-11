#include "BombComponent.h"
#include "Entity.h"
#include "EventManager.h"
#include "Game.h"
#include "Level.h"
#include "Log.h"

#include <stdlib.h>

using namespace std;

BombComponent::BombComponent(Game* game, Entity* entity, float speed) : Component(game, entity)
{
	this->speed = speed;
	SubscribeToEvent(EventType::Update, this, &BombComponent::HandleUpdate);
	SubscribeToEvent(EventType::Collision, this, &BombComponent::HandleCollision);
}


BombComponent::~BombComponent()
{
	UnsubscribeFromEvent(EventType::Update, this);
	UnsubscribeFromEvent(EventType::Collision, this);
}

void BombComponent::HandleUpdate(Object * sender, const EventDataMap& eventData)
{
	float deltaTime = game->GetDeltaTime();
	entity->Translate(0.f, speed * deltaTime);
}

void BombComponent::HandleCollision(Object * sender, const EventDataMap& eventData)
{
	Entity* collidedEntity = (Entity*)eventData.at("Other").GetVoidPtr();
	if(!collidedEntity->HasComponent(ComponentType::Drone))
	{
		//Log::Message("Bomb Collided with %s", collidedEntity->GetName().c_str());
		Level* level = game->GetLevel();
		level->RemoveEntity(entity);
	}
}
