#include "SpriteAnimationComponent.h"
#include "Entity.h"
#include "Game.h"

SpriteAnimationComponent::SpriteAnimationComponent(Game * game, Entity * entity, int frames, float speed, bool loop) : 
	Component(game, entity), 
	numFrames(frames),
	animationSpeed(speed),
	looped(loop)
{
	sf::Sprite* sprite = entity->GetSprite();
	const sf::Texture* texture = sprite->getTexture();

	//Determine the width and height of a single frame
	frameWidth = texture->getSize().x / numFrames;
	frameHeight = texture->getSize().y;

	//Determine the interval(in seconds) after which we should go the next frame
	interval = 1.f / (float)numFrames; 

	//Set the sprite's rect to the first frame
	sprite->setTextureRect(sf::IntRect(0, 0, currentFrame * frameWidth, frameHeight));

	SubscribeToEvent(EventType::Update, this, &SpriteAnimationComponent::HandleUpdate);
}

SpriteAnimationComponent::~SpriteAnimationComponent()
{
	UnsubscribeFromEvent(EventType::Update, this);
}

void SpriteAnimationComponent::Play()
{
	currentState = Playing;
}

void SpriteAnimationComponent::Stop()
{
	currentState = Stopped;
	timeElapsed = 0.f;
	currentFrame = 1;
	sf::Sprite* sprite = entity->GetSprite();
	sprite->setTextureRect(sf::IntRect(0, 0, currentFrame * frameWidth, frameHeight));
}

void SpriteAnimationComponent::Pause()
{
	currentState = Paused;
}

void SpriteAnimationComponent::SetLoop(bool loop)
{
	looped = loop;
}

void SpriteAnimationComponent::HandleUpdate(Object* sender, const EventDataMap & eventData)
{
	sf::Sprite* sprite = entity->GetSprite();
	if(currentState == Playing)
	{
		timeElapsed += (game->GetDeltaTime() * animationSpeed);
		if(timeElapsed >= interval)
		{
			timeElapsed = 0.f;
			currentFrame++;
			if(currentFrame > numFrames)
			{
				if(!looped)
				{
					Stop();
					return;
				}
				else
				{
					currentFrame = 1;
				}
			}
			sprite->setTextureRect(sf::IntRect((currentFrame - 1) * frameWidth, 0, frameWidth, frameHeight));
		}
	}
}

