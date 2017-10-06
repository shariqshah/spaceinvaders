#pragma once

#include "EventManager.h"

#define SubscribeToEvent(type, instance, method) \
{\
	EventManager* manager = game->GetEventManager();\
	manager->SubscribeEvent(type, instance, std::bind(this, method, std::placeholders::_1, std::placeholders::_2)); \
}\

#define UnsubscribeFromEvent(type, subscriber) \
{\
	EventManager* manager = game->GetEventManager();\
	manager->UnsubscribeEvent(type, subscriber);\
}\

class Object
{
public:
	Object();
	~Object();

private:
	Game* game = NULL;
};
