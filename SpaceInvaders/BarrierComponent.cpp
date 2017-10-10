#include "BarrierComponent.h"
#include "Game.h"
#include "ResourceManager.h"
#include "SoundComponent.h"
#include "Entity.h"
#include "Level.h"

BarrierComponent::BarrierComponent(Game * game, Entity * entity, int startingHealth) : Component(game, entity), health(startingHealth)
{
	SubscribeToEvent(EventType::Collision, this, &BarrierComponent::HandleCollision);
}

BarrierComponent::~BarrierComponent()
{
	UnsubscribeFromEvent(EventType::Collision, this);
}

void BarrierComponent::HandleCollision(Object * sender, const EventDataMap & eventData)
{
	Entity* other = (Entity*)eventData.at("Other").GetVoidPtr();
	if(other->HasComponent(ComponentType::Bomb))
	{
		// Reduce health on hit
		health -= onHitDamage;

		SoundComponent* soundComponent = entity->GetComponent<SoundComponent>();
		if(soundComponent)
		{
			Game::Settings* settings = game->GetSettings();
			if(settings->soundOn)
				soundComponent->PlayDefault();
		}

		if(health <= 0)
		{
			Level* level = game->GetLevel();
			level->RemoveEntity(entity);
		}
	}
}
