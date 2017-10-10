#include "SweeperComponent.h"
#include "SoundComponent.h"
#include "Game.h"
#include "Entity.h"
#include "Level.h"


SweeperComponent::SweeperComponent(Game * game, Entity * entity) : Component(game, entity)
{
	SubscribeToEvent(EventType::Update, this, &SweeperComponent::HandleUpdate);
	SubscribeToEvent(EventType::LevelStart, this, &SweeperComponent::HandleLevelStart);
	SubscribeToEvent(EventType::Collision, this, &SweeperComponent::HandleCollision);
	entity->SetPosition(game->GetWindowWidth() + 10000, 0.f);
}

SweeperComponent::~SweeperComponent()
{
	UnsubscribeFromEvent(EventType::Update, this);
	UnsubscribeFromEvent(EventType::LevelStart, this);
	UnsubscribeFromEvent(EventType::Collision, this);
}

void SweeperComponent::HandleUpdate(Object * sender, const EventDataMap & eventData)
{
	const float appearanceInterval = 20.f;
	if(clock.getElapsedTime().asSeconds() >= appearanceInterval && !active)
	{
		active = true;
		Level* level = game->GetLevel();
		entity->SetPosition(game->GetWindowWidth() - level->GetMarginX(), level->GetMarginY());
		SoundComponent* soundComponent = entity->GetComponent<SoundComponent>();
		if(soundComponent)
		{
			if(game->GetSettings()->soundOn)
			{
				soundComponent->Play("Sounds/SweeperMove.wav");
				soundComponent->SetLooped("Sounds/SweeperMove.wav", true);
			}
		}
	}

	//Handle Active logic here
	if(active)
	{
		// Or maybe treat this as a normal entity and spawn it every 10 seconds or so and handle the
		// spawn logic inside level?
		entity->Translate(game->GetDeltaTime() * -speed, 0.f);
		sf::Sprite* sprite = entity->GetSprite();
		if(entity->GetPositionX() + sprite->getLocalBounds().width <= 0)
		{
			active = false;
			clock.restart();
			SoundComponent* soundComponent = entity->GetComponent<SoundComponent>();
			if(soundComponent)
			{
				soundComponent->Stop("Sounds/SweeperMove.wav");
			}
		}
	}
}

void SweeperComponent::HandleCollision(Object * sender, const EventDataMap & eventData)
{
	Entity* other = (Entity*)eventData.at("Other").GetVoidPtr();
	if(other->HasComponent(ComponentType::Missile))
	{
		//reset position and award the player an extra life
		entity->SetPosition(game->GetWindowWidth() + 10000, 0.f);

		game->GetPlayerState()->score += hitScoreReward;
		game->GetPlayerState()->lives += hitLifeReward;

		SoundComponent* soundComponent = entity->GetComponent<SoundComponent>();
		if(soundComponent)
		{
			if(game->GetSettings()->soundOn)
			{
				soundComponent->Play("Sounds/SweeperHit.wav");
				soundComponent->Stop("Sounds/SweeperMove.wav");
			}
		}
		active = false;
		clock.restart();
		game->GetLevel()->UpdatePlayerStatsText();
	}
}

void SweeperComponent::HandleLevelStart(Object * sender, const EventDataMap & eventData)
{
	clock.restart();
}
