#include "CannonComponent.h"
#include "Entity.h"
#include "EventManager.h"
#include "MissileComponent.h"
#include "Level.h"
#include "ResourceManager.h"
#include "Game.h"

#include <SFML\System.hpp>

using namespace std;

CannonComponent::CannonComponent(Game * game, Entity * entity, float speed) : Component(game, entity), moveSpeed(speed)
{
	// Register to relevant events
	SubscribeToEvent(EventType::KeyDown, this, &CannonComponent::HandleKeyDown);
}

CannonComponent::~CannonComponent()
{
	UnsubscribeFromEvent(EventType::KeyDown, this);
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
	}

	if(move != 0.f)
	{
		entity->Translate(move, 0.f);
	}
}
