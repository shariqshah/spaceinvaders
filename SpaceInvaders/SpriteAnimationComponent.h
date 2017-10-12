#pragma once

#include "Component.h"

#include <SFML\System.hpp>

/*

Animation Component that uses the sprite contained in the Entity as the basis for animation
In order to make things a bit simpler, there are some constraints on the image being
used for the animation:
- Animation's frames are always expected to go from left to right
- All frames must have the same height and width
- There must only be one animation in an image

*/

class SpriteAnimationComponent : public Component
{
public:
	enum State
	{
		Playing = 0,
		Paused,
		Stopped
	};

	SpriteAnimationComponent() {};
	SpriteAnimationComponent(Game* game, Entity* entity, int frames, float speed = 1.f, bool looped = true);
	virtual ~SpriteAnimationComponent();

	virtual ComponentType GetType() override { return ComponentType::SpriteAnimation; };

	void Play();
	void Stop();
	void Pause();
	void SetLoop(bool loop);
	State GetState() const { return currentState; }
private:
	void HandleUpdate(Object* sender, const EventDataMap& eventData);

	State currentState = Playing;
	int frameHeight = 0.f;
	int frameWidth= 0.f;
	int numFrames = 1;
	int currentFrame = 0;
	float timeElapsed = 0.f;
	float animationSpeed = 1.f;
	float interval = 0.f;
	bool looped = true;
	sf::Clock clock;
};

