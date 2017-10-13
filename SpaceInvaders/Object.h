#pragma once

#include "EventManager.h"

/*Convenience macro that gets the event manager and subscribes to an event */
#define SubscribeToEvent(type, instance, method) \
{\
	EventManager* manager = game->GetEventManager();\
	manager->SubscribeEvent(type, instance, std::bind(method, instance, std::placeholders::_1, std::placeholders::_2)); \
}\

/*Convenience macro that gets the event manager and unsubscribes to an event */
#define UnsubscribeFromEvent(type, subscriber) \
{\
	EventManager* manager = game->GetEventManager();\
	manager->UnsubscribeEvent(type, subscriber);\
}\

class Game;


// Base object class. Any object that needs to send or recieve events needs to inherit from this class
class Object
{
public:
	Object() : game(NULL) {};
	Object(Game* gameInstance);
	virtual ~Object();
	Object(const Object& other) : game(other.GetGame()){}

	Game* GetGame() const { return game; };
protected:
	Game* game = NULL;
};
