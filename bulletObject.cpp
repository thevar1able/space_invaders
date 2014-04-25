#include "bulletObject.h"

bulletObject::bulletObject(basicObject* playerPlatform) : basicObject({playerPlatform->getGeometry().x + 23, SCREEN_WIDTH + 60, 15, 3})
{
	this->isExist = true;
	basicObject::drawRect(this->shape, 0, 0, 3, 15, 0xffffff);
}

int bulletObject::draw(SDL_Surface* pSDLSurface)
{
	this->move(0, -3);
	basicObject::draw(pSDLSurface);
	if(this->objectGeometry.y < -this->shape->h || !this->isExist) return -1;
	return 0;
}

void bulletObject::handleEvents(std::vector<basicEvent*>* eventQueue)
{
	for (auto i = 0; i < eventQueue->size(); ++i)
	{
		if(eventQueue->at(i)->eventType == COLLISION)
		{
			// this->isExist = false;
		}
	}
	return;
}