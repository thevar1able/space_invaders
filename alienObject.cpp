#include "alienObject.h"

alienObject::alienObject(int x, int y)
{
	this->isExist = true;
	basicObject::setCoords(x, y);

	basicObject::drawRect(this->shape, 0, 0, 50, 50, 0xffffff);
}

int alienObject::draw(SDL_Surface* pSDLSurface)
{
	if(!this->isExist)
	{
		return -1;
	}
	else
	{
		basicObject::draw(pSDLSurface);
	} 
	return 0;
}

void alienObject::move(int x, int y)
{
	basicObject::move(x, y);
}

void alienObject::handleEvents(std::vector<basicEvent*>* eventQueue)
{
	for (auto i = 0; i < eventQueue->size(); ++i)
	{
		if(eventQueue->at(i)->eventType == COLLISION && eventQueue->at(i)->objectPointer == this)
		{
			this->isExist = false;
		}
	}
	return;
}