#include "Common.h"
#include "Component.h"

std::string Common::ComponentTypeToString(ComponentType type)
{
	switch(type)
	{
	case ComponentType::Barrier: return std::string("Barrier");
	case ComponentType::Bomb:    return std::string("Bomb");
	case ComponentType::Cannon:  return std::string("Cannon");
	case ComponentType::Missile: return std::string( "Missile");
	case ComponentType::Drone:   return std::string("Drone");
	case ComponentType::Ground:  return std::string("Ground");
	case ComponentType::None:    return std::string("None");
	case ComponentType::Music:   return std::string("Music");
	case ComponentType::Sound:   return std::string("Sound");
	case ComponentType::Len:     return std::string("Len");
	default: return std::string("Invalid Component Type");
	}
}
