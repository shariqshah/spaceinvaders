#include "Component.h"

Component::Component(Game* game, Entity* entity)
{
	this->game = game;
	this->entity = entity;
}


Component::~Component()
{
}
