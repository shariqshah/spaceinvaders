#pragma once

#include "EventManager.h"

#define SubscribeToEvent(type, instance, method) \
{\
	EventManager* manager = game->GetEventManager();\
	manager->SubscribeEvent(type, instance, std::bind(method, instance, std::placeholders::_1, std::placeholders::_2)); \
}\

#define UnsubscribeFromEvent(type, subscriber) \
{\
	EventManager* manager = game->GetEventManager();\
	manager->UnsubscribeEvent(type, subscriber);\
}\

class Game;

class Object
{
public:
	Object() : game(NULL) {};
	Object(Game* gameInstance);
	~Object();
	Object(const Object& other) : game(other.GetGame()){}

	Game* GetGame() const { return game; };
protected:
	Game* game = NULL;
};
