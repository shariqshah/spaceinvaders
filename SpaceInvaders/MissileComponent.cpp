#include "MissileComponent.h"
#include "Entity.h"
#include "EventManager.h"
#include "Game.h"
#include "Level.h"
#include "Log.h"

#include <stdlib.h>

using namespace std;

MissileComponent::MissileComponent(Game* game, Entity* entity, float speed) : Component(game, entity), speed(speed)
{
	SubscribeToEvent(EventType::Update, this, &MissileComponent::HandleUpdate);
	SubscribeToEvent(EventType::Collision, this, &MissileComponent::HandleCollision);
}

MissileComponent::~MissileComponent()
{
	UnsubscribeFromEvent(EventType::Update, this);
	UnsubscribeFromEvent(EventType::Collision, this);
}

void MissileComponent::HandleCollision(Object * sender, const EventDataMap & eventData)
{
	Entity* other = (Entity*)eventData.at("Other").GetVoidPtr();
	if(other->HasComponent(ComponentType::Drone) || other->HasComponent(ComponentType::Bomb))
	{
		Level* level = game->GetLevel();
		level->RemoveEntity(entity);
		level->RemoveEntity(other);
	}
}

void MissileComponent::HandleUpdate(Object * sender, const EventDataMap & eventData)
{
	float deltaTime = game->GetDeltaTime();

	if(entity->GetPositionY() < 0.f)
	{
		Level* level = game->GetLevel();
		level->RemoveEntity(entity);
	}
	entity->Translate(0.f, speed * deltaTime);
}
