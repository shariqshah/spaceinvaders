#pragma once

#include "Events.h"
#include "Variant.h"

#include <vector>
#include <map>
#include <string>
#include <functional>

class Object;
class Entity;

// Some typedefs to make functions a bit less verbose
typedef std::map<std::string, Variant> EventDataMap;
typedef std::function<void(Object* sender, const EventDataMap& data)> EventHandler;

/*
Represents an event subscription. Holds the event type that is subscribed to, the object
that has subscribed and which method  of the object to call when that event occurs
*/
struct EventSubscription
{
	EventType    type;
	Object*      subscriber = NULL;
	EventHandler onEvent;

	EventSubscription(EventType eventType, Object* eventSubscriber, EventHandler handler)
		: type(eventType), subscriber(eventSubscriber), onEvent(handler)
	{}

	EventSubscription(const EventSubscription& other)
		: type(other.type), subscriber(other.subscriber), onEvent(other.onEvent)
	{}
};

/*
All objects that want to subscibe to a particular event or send an event must us the 
event manager. Event manager contains all the objects that have currently subscribed to 
events and the parameter data that is sent when a particluar event occurs. Event parameter
data is clear every frame.
*/
class EventManager
{
	std::vector<EventSubscription> subscriptions;
	std::map<std::string, Variant> eventData;
public:
	EventManager();
	~EventManager();

	void SubscribeEvent(EventType type, Object* subscriber, EventHandler onEvent);
	bool UnsubscribeEvent(EventType type, Object* subscriber);
	void SendEvent(EventType type, Object* sender, const EventDataMap& data);
	void SendEvent(EventType type);
	void SendEvent(EventType type, Object* sender, Object* reciever, const EventDataMap& data);
	void SendEvent(EventType type, Object* sender, Entity* reciever, const EventDataMap& data);
	bool IsSubscribed(EventType type, Object* object);

	EventDataMap& GetEventDataMap() { return eventData; } // Call this before sending an event and put all the event data inside the returned map
	void ResetEventDataMap(); // This is called after each frame, event data is reset for the next frame
};
