#include "basicObject.h"

basicObject::basicObject()
{
		this->shape = SDL_CreateRGBSurface(SDL_HWSURFACE, 50, 50, 32, 0, 0, 0, 0);
		SDL_SetColorKey(this->shape, SDL_SRCCOLORKEY, 0);
}

basicObject::basicObject(int h, int w)
{
	if(w <= SCREEN_WIDTH && h <= SCREEN_HEIGHT)
	{
		this->shape = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, 32, 0, 0, 0, 0);
		SDL_SetColorKey(this->shape, SDL_SRCCOLORKEY, 0);
	}
}

basicObject::basicObject(geometry objectGeometry)
{
	if(objectGeometry.w <= SCREEN_WIDTH && objectGeometry.h <= SCREEN_HEIGHT)
	{
		this->shape = SDL_CreateRGBSurface(SDL_HWSURFACE, objectGeometry.w, objectGeometry.h, 32, 0, 0, 0, 0);
		SDL_SetColorKey(this->shape, SDL_SRCCOLORKEY, 0);
		this->objectGeometry = objectGeometry;
	}
}

void basicObject::move(int dX, int dY)
{
	this->objectGeometry.x += dX;
	this->objectGeometry.y += dY;
}

void basicObject::setCoords(int x, int y)
{
	this->objectGeometry.x = x;
	this->objectGeometry.y = y;
}

int basicObject::draw(SDL_Surface* pSDLScreen)
{
	SDL_Rect dest_pos {(Sint16)this->objectGeometry.x, (Sint16)this->objectGeometry.y};

	SDL_BlitSurface(this->shape, NULL, pSDLScreen, &dest_pos);	
	return 0;
}

void basicObject::drawRect(SDL_Surface* screen, int x, int y, int width, int height, int color)
{
    SDL_Rect rect {(Sint16)x, (Sint16)y, (Uint16)width, (Uint16)height};
    SDL_FillRect(screen, &rect, color);
}

geometry basicObject::getGeometry()
{
	return this->objectGeometry;
}