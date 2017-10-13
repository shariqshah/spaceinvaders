#pragma once

#include "Object.h"

class Entity;

enum class ComponentType
{
	None = 0,
	Cannon,
	Barrier,
	Bomb,
	Missile,
	Drone,
	Ground,
	Sound,
	Music,
	Sweeper,
	SpriteAnimation,
	Len
};

/*
Base Component type that  all components inherit from. Each component type
that inherits from this class returns it's unique value which must be added 
to the ComponentType enum above.
*/
class Component : public Object
{
public:
	Component() : entity(NULL) {};
	Component(Game* game, Entity* entity);
	virtual ~Component();

	virtual ComponentType GetType() = 0;
	Entity* GetEntity() { return entity; }
protected:
	Entity* entity = NULL;
};

