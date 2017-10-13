#include "BarrierComponent.h"
#include "SpriteAnimationComponent.h"
#include "Game.h"
#include "ResourceManager.h"
#include "SoundComponent.h"
#include "Entity.h"
#include "Level.h"

using namespace std;

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

		SoundComponent* soundComponent = (SoundComponent*)entity->GetComponent(ComponentType::Sound);
		if(soundComponent)
		{
			Game::Settings* settings = game->GetSettings();
			if(settings->soundOn)
				soundComponent->PlayDefault();
		}

		if(health <= 0)
		{
			// Remove barrier from list of barriers and remove entity altogether
			Level* level = game->GetLevel();
			vector<Entity*>& barriers = level->GetBarriers();
			int index = -1;
			for(int i = 0; i < barriers.size(); i++)
			{
				if(barriers[i] == entity)
				{
					index = i;
					break;
				}
			}

			if(index != -1)
			{
				barriers.erase(barriers.begin() + index);
			}

			level->RemoveEntity(entity);
		}
		else
		{
			//Move animation one frame forward to show barrier is damaged
			if(health == 60 || health == 40 || health == 20)
			{
				SpriteAnimationComponent* animation = (SpriteAnimationComponent*)entity->GetComponent(ComponentType::SpriteAnimation);
				animation->MoveToNextFrame();
			}
		}
	}
}
