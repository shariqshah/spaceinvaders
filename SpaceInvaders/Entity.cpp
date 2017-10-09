#include "Entity.h"
#include "Component.h"
#include "Common.h"
#include "Log.h"

using namespace std;

Entity::Entity(Game * game, const string& name)
{
	this->game = game;
	this->name = name;
}

Entity::~Entity()
{
	for(Component* component : components)
	{
		if(component)
		{
			delete component;
			component = NULL;
		}
	}
}

bool Entity::isColliding(Entity * entity)
{
	if(!entity)
	{
		Log::Error("Entity:IsColliding", "Null Entity");
		return false;
	}

	sf::Sprite* otherSprite = entity->GetSprite();
	if(sprite.getGlobalBounds().intersects(otherSprite->getGlobalBounds()))
	{
		return true;
	}

	return false;
}

Component* Entity::AddComponent(Component * component)
{
	if(!component)
	{
		Log::Error("Entity:AddComponent", "Component is NULL");
		return NULL;
	}

	ComponentType type = component->GetType();
	if(type == ComponentType::None || type == ComponentType::Len)
	{
		Log::Error("Entity:AddComponent", "Invalid component type '%s'", Common::ComponentTypeToString(type).c_str());
		return NULL;
	}

	if(!HasComponent(type))
	{
		components.push_back(component);
		Log::Message("Component '%s' added to '%s'", Common::ComponentTypeToString(type).c_str(), name.c_str());
		return component;
	}
	else
	{
		Log::Message("Entity '%s' already has '%s' component", name.c_str(), Common::ComponentTypeToString(type));
		return NULL;
	}
}

bool Entity::HasComponent(ComponentType type)
{
	for(Component* component : components)
	{
		if(component->GetType() == type)
		{
			return true;
		}
	}
	return false;
}

bool Entity::RemoveComponent(ComponentType type)
{
	int index = -1;
	for(int i = 0; i < components.size(); i++)
	{
		if(components[i]->GetType() == type)
		{
			index = -1;
			break;
		}
	}

	if(index == -1)
	{
		return false;
	}

	components.erase(components.begin() + index);
	Log::Message("Component '%s' removed from '%s'", Common::ComponentTypeToString(type).c_str(), name.c_str());
	return true;
}