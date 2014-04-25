#include <SDL/SDL.h>
#include <vector>
#include "screenSize.h"
#include "events.h"

#ifndef _BASICOBJECT_H_
#define _BASICOBJECT_H_

struct sGeometry
{
	int x, y, h, w;
};

typedef struct sGeometry geometry;

class basicObject : public IBasicObject
{
	protected:
		geometry objectGeometry = {0};
		SDL_Surface* shape;
	public:
		basicObject();
		basicObject(geometry);
		basicObject(int, int);
		void setCoords(int, int);
		virtual void move(int, int);
		virtual int draw(SDL_Surface*);
		virtual void handleEvents(std::vector<basicEvent*>*) = 0;
		geometry getGeometry();
		void drawRect(SDL_Surface*, int, int, int, int, int);
};

#endif