#include "EventManager.h"
#include "Entity.h"
#include "Component.h"

using  namespace std;

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::SubscribeEvent(EventType type, Object * subscriber, EventHandler onEvent)
{
	subscriptions.push_back(EventSubscription(type, subscriber, onEvent));
}

bool EventManager::UnsubscribeEvent(EventType type, Object * subscriber)
{
	int index = -1;
	for(int i = 0; i < subscriptions.size(); i++)
	{
		if(subscriptions[i].type == type && subscriptions[i].subscriber == subscriber)
		{
			index = i;
			break;
		}
	}

	if(index == -1) return false;

	subscriptions.erase(subscriptions.begin() + index);
	return true;
}

void EventManager::SendEvent(EventType type, Object * sender, const EventDataMap& data)
{
	for(EventSubscription& subscription : subscriptions)
	{
		if(subscription.type == type)
		{
			subscription.onEvent(sender, data);
		}
	}
}

void EventManager::SendEvent(EventType type, Object * sender, Object * reciever, const EventDataMap& data)
{
	for(EventSubscription& subscription : subscriptions)
	{
		if(subscription.type == type && subscription.subscriber == reciever)
		{
			subscription.onEvent(sender, data);
			break;
		}
	}
}

void EventManager::SendEvent(EventType type, Object * sender, Entity * reciever, const EventDataMap& data)
{
	auto components = reciever->GetComponents();
	for(Component* component : components)
	{
		SendEvent(type, sender, component, data);
	}
}

bool EventManager::IsSubscribed(EventType type, Object * object)
{
	for(EventSubscription& subscription : subscriptions)
	{
		if(subscription.type == type && subscription.subscriber == object)
		{
			return true;
		}
	}
	return false;
}

void EventManager::ResetEventDataMap()
{
	eventData.clear();
}
