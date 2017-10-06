#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <time.h>

#include "Log.h"
#include "Game.h"

float calcDistance(const sf::Vector2f& v1, const sf::Vector2f& v2);


//struct Entity
//{
//	sf::Texture texture;
//
//	float speed = 250.f;
//	float currentSpeed = speed;
//
//	sf::Color normalColor = sf::Color::Blue;
//	sf::Color collisionColor = sf::Color::Red;
//
//	virtual void Update(float deltaTime, sf::RenderWindow& window) = 0;
//	virtual void Draw(sf::RenderWindow& window) = 0;
//	virtual bool IsColliding(std::vector<Entity*>& entities) = 0;
//};
//
//
//struct RectEntity : Entity
//{
//	sf::Sprite sprite;
//
//	RectEntity(const std::string& filename, const sf::IntRect& rect)
//	{
//		if(!texture.loadFromFile("GameData/Textures/image.png"))
//		{
//			Log::Error("Main", "Failed to load image.png");
//			return;
//		}
//		sprite.setTexture(texture);
//		sprite.setTextureRect(rect);
//		sprite.setColor(normalColor);
//	}
//
//	virtual void Update(float deltaTime, sf::RenderWindow& window) override
//	{
//		if(sprite.getPosition().x >= (window.getSize().x - sprite.getLocalBounds().width))
//			currentSpeed = -speed;
//		else if(sprite.getPosition().x <= 0)
//			currentSpeed = speed;
//		sprite.move(currentSpeed * deltaTime, 0.f);
//	}
//
//	virtual void Draw(sf::RenderWindow& window) override
//	{
//		window.draw(sprite);
//	}
//
//	virtual bool IsColliding(std::vector<Entity*>& entities) override
//	{
//		sprite.setColor(normalColor);
//		for(Entity* entity : entities)
//		{
//			// Ignore collisions with self
//			if(entity == this)
//				 continue;
//
//			RectEntity* ent = dynamic_cast<RectEntity*>(entity);
//			if(!ent)
//			{
//				// We only support rect to rect collisions
//				continue;
//			}
//
//			if(ent->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
//			{
//				// This sprite is colliding with at least one other sprite, change color
//				sprite.setColor(collisionColor);
//				ent->sprite.setColor(collisionColor);
//				return true;
//			}
//		}
//		return false;
//	}
//};
//
//struct CircleEntity : public Entity
//{
//	sf::CircleShape circle;
//
//	CircleEntity(const std::string& filename, const sf::IntRect& rect, float radius)
//	{
//		if(!texture.loadFromFile("GameData/Textures/image.png"))
//		{
//			Log::Error("Main", "Failed to load image.png");
//			return;
//		}
//		circle.setTexture(&texture);
//		circle.setTextureRect(rect);
//		circle.setRadius(radius);
//		circle.setFillColor(normalColor);
//	}
//
//	virtual void Update(float deltaTime, sf::RenderWindow& window) override
//	{
//		if(circle.getPosition().x >= (window.getSize().x - circle.getRadius() * 2.f))
//			currentSpeed = -speed;
//		else if(circle.getPosition().x <= 0)
//			currentSpeed = speed;
//		circle.move(currentSpeed * deltaTime, 0.f);
//	}
//
//	virtual void Draw(sf::RenderWindow& window) override
//	{
//		window.draw(circle);
//	}
//
//	virtual bool IsColliding(std::vector<Entity*>& entities) override
//	{
//		circle.setFillColor(normalColor);
//		for(Entity* entity : entities)
//		{
//			// Ignore collisions with self
//			if(entity == this)
//				continue;
//
//			CircleEntity* ent = dynamic_cast<CircleEntity*>(entity);
//			if(!ent)
//			{
//				// We only support rect to rect collisions
//				continue;
//			}
//
//			//Check for circle collisions by getting the distance between the origins
//			//of both circles and if that distance is smaller or equal to the sum radii
//			//of both circles then the circles are colliding
//			float distance = calcDistance(ent->circle.getPosition(), circle.getPosition());
//			if(distance <= (ent->circle.getRadius() + circle.getRadius()))
//			{
//				ent->circle.setFillColor(collisionColor);
//				circle.setFillColor(collisionColor);
//				return true;
//			}
//		}
//		return false;
//	}
//};

int main(int argc, const char** argv)
{
	Game game;
	game.Run();

	Log::Message("Game exiting...");

	return 0;
}

float calcDistance(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	sf::Vector2f diff = v2 - v1;
	float distance = sqrtf((diff.x * diff.x) + (diff.y * diff.y));
	return fabsf(distance);
}