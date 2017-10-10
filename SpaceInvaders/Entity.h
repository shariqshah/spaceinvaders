#pragma once

#include "Object.h"

#include <SFML\Graphics.hpp>
#include <vector>

class Component;
enum class ComponentType;

class Entity : public Object
{
public:
	Entity() {};
	Entity(Game* game, const std::string& name);
	~Entity();

	bool isColliding(Entity* entity);
	std::string GetName() { return name; };
	sf::Sprite* GetSprite() { return &sprite; }
	void SetName(const std::string& entityName) { name = entityName; }
	Component* AddComponent(Component* component);
	bool HasComponent(ComponentType type);
	bool RemoveComponent(ComponentType type);
	std::vector<Component*>& GetComponents() { return components; };

	template<class T>
	T* GetComponent() 
	{
		T temp;
		for(Component* component : components)
		{
			if(component->GetType() == temp.GetType())
			{
				return static_cast<T*>(component);
			}
		}
		return NULL;
	}

	//Convenience methods for entity transformation
	void SetPosition(float x, float y) { sprite.setPosition(x, y); };
	void SetRotation(float angle) { sprite.setRotation(angle); }
	void SetScale(float scaleX, float scaleY) { sprite.setScale(scaleX, scaleY); }

	void Translate(float offsetX, float offsetY) { sprite.move(offsetX, offsetY); }
	void Rotate(float angle) { sprite.rotate(angle); }
	void Scale(float scaleX, float scaleY) { sprite.scale(scaleX, scaleY); }

	sf::Vector2f GetPosition() { return sprite.getPosition(); }
	float GetPositionX() { return sprite.getPosition().x; }
	float GetPositionY() { return sprite.getPosition().y; }

	float GetScaleX() { return sprite.getScale().x; }
	float GetScaleY() { return sprite.getScale().y; }

	bool IsCheckedForCollisions() { return checkedForCollisions; }
	void SetCheckedForCollisions(bool checked) { checkedForCollisions = checked; }

	bool IsMarkedForDeletion() { return markedForDeletion; }
	void SetMarkedForDeletion(bool mark) { markedForDeletion = mark; }

private:
	std::string name;
	std::vector<Component*> components;
	sf::Sprite sprite;
	bool checkedForCollisions = false;
	bool markedForDeletion = false;
};

