#pragma once


// Each event type can have zero or more parameters which the event handler can retrieve 
// from the EventDataMap when the handler is called. 
// When sending the event these parameters must be filled with their appropriate values
// since that is what the event handler expects.
// It must be noted however that the name of each parameter must be unique since events
// can be chained and if two event parameters share the same name their value may be overwritten
// in the EventDataMap.

enum class EventType
{
	KeyDown,         // Params: Key : Enum(int), Control : bool, Shift : bool
	KeyUp,           // Params: Key : Enum(int), Control : bool, Shift : bool
	Update,          // Params: DeltaTime : float
	PostUpdate,      // Params: None
	LevelStart,      // Params: None
	LevelEnd,        // Params: None
	Collision,       // Params: Other : Entity*
	DroneDestroyed,  // Params: DroneType : DroneType
	Len
};