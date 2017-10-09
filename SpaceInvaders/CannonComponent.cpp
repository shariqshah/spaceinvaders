#include "CannonComponent.h"
#include "Entity.h"
#include "EventManager.h"
#include "MissileComponent.h"
#include "Level.h"
#include "ResourceManager.h"
#include "Game.h"
#include "SoundComponent.h"

#include <SFML\System.hpp>

using namespace std;

CannonComponent::CannonComponent(Game * game, Entity * entity, float speed) : Component(game, entity), moveSpeed(speed)
{
	// Register to relevant events
	SubscribeToEvent(EventType::KeyDown, this, &CannonComponent::HandleKeyDown);
	SubscribeToEvent(EventType::Collision, this, &CannonComponent::HandleCollision);
}

CannonComponent::~CannonComponent()
{
	UnsubscribeFromEvent(EventType::KeyDown, this);
	UnsubscribeFromEvent(EventType::Collision, this);
}

void CannonComponent::HandleKeyDown(Object * sender, const EventDataMap& eventData)
{
	using sf::Keyboard;
	Keyboard::Key key = (Keyboard::Key)eventData.at("Key").GetInt();

	float move = 0.f;
	if(key == Keyboard::Right)
	{
		move += (moveSpeed * game->GetDeltaTime());
	}
	else if(key == Keyboard::Left)
	{
		move -= (moveSpeed * game->GetDeltaTime());
	}
	
	if(key == Keyboard::Space)
	{
		Entity* missile = new Entity(game, "Missile" + to_string(clock.getElapsedTime().asMilliseconds()));
		missile->AddComponent(new MissileComponent(game, missile, -200.f));

		sf::Sprite* missileSprite = missile->GetSprite();
		ResourceManager* resourceManager = game->GetResourceManager();
		sf::Texture* missileTexture = resourceManager->GetTexture("Textures/missile.png");
		missileSprite->setTexture(*missileTexture);

		sf::Vector2f currPos = entity->GetPosition();
		const sf::Texture* droneTex = entity->GetSprite()->getTexture();
		float halfTextureWidth = droneTex->getSize().x / 4.f;
		missile->SetPosition(currPos.x + halfTextureWidth, entity->GetPositionY());

		Level* level = game->GetLevel();
		level->AddEntity(missile);

		SoundComponent* soundComponent = entity->GetComponent<SoundComponent>();
		if(soundComponent)
		{
			soundComponent->Play("Sounds/CannonShoot.wav");
		}
	}

	if(move != 0.f)
	{
		entity->Translate(move, 0.f);
	}
}

void CannonComponent::HandleCollision(Object * sender, const EventDataMap & eventData)
{
	Entity* other = (Entity*)eventData.at("Other").GetVoidPtr();
	if(other->HasComponent(ComponentType::Bomb))
	{
		// We're hit by a bomb, reduce life and check if it's game over
		game->GetPlayerState()->lives--;
		game->GetLevel()->UpdateLivesText();
		if(game->GetPlayerState()->lives == 0)
		{
			game->SetCurrentState(Game::State::GameOver);
		}

		SoundComponent* soundComponent = entity->GetComponent<SoundComponent>();
		if(soundComponent)
		{
			soundComponent->Play("Sounds/CannonHit.wav");
		}
	}
}
