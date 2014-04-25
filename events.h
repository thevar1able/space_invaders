#include <SDL/SDL.h>

#ifndef _EVENTS_H_
#define _EVENTS_H_

enum eventTypes { SDL, COLLISION };

class IBasicObject
{

};

class basicEvent
{
	public:
		basicEvent(eventTypes, SDL_Event);
		basicEvent(eventTypes, IBasicObject*);
		eventTypes eventType;
		SDL_Event event;
		IBasicObject* objectPointer;
};
#endif