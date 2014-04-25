#include "events.h"

basicEvent::basicEvent(eventTypes eventType, SDL_Event event)
{
	this->eventType = eventType;
	this->event = event;
	this->objectPointer = NULL;
}

basicEvent::basicEvent(eventTypes eventType, IBasicObject* objectPointer)
{
	this->eventType = eventType;
	this->objectPointer = objectPointer;
}