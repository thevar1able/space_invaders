#include "playerPlatform.h"

playerPlatform::playerPlatform() : basicObject()
{
	leftArrowPressed = 0;
	rightArrowPressed = 0;

	this->objectGeometry.y = SCREEN_WIDTH + 40;

	basicObject::drawRect(this->shape, 0, 40, 50, 10, 0xffffff);
	basicObject::drawRect(this->shape, 22, 20, 6, 25, 0xffffff);
}

int playerPlatform::draw(SDL_Surface* pSDLSurface)
{
	basicObject::draw(pSDLSurface);
	return 0;
}

void playerPlatform::handleEvents(std::vector<basicEvent*>* eventBuffer)
{
	for (auto i = 0; i < eventBuffer->size(); ++i)
	{
		if(eventBuffer->at(i)->event.type == SDL_KEYDOWN)
		{
			switch(eventBuffer->at(i)->event.key.keysym.sym)
			{
				case SDLK_LEFT: this->leftArrowPressed = true; break;
				case SDLK_RIGHT: this->rightArrowPressed = true; break;
			}
			// printf("Down!\n");
		}
		else if(eventBuffer->at(i)->event.type == SDL_KEYUP)
		{
			switch(eventBuffer->at(i)->event.key.keysym.sym)
			{
				case SDLK_LEFT: this->leftArrowPressed = false; break;
				case SDLK_RIGHT: this->rightArrowPressed = false; break;
			}
			// printf("Up!\n");
		}
	}
	if(leftArrowPressed) this->move(-STEP, 0);
	if(rightArrowPressed) this->move(STEP, 0);
}

void playerPlatform::move(int x, int y)
{
	if(this->objectGeometry.x + x <= SCREEN_WIDTH - this->shape->w && this->objectGeometry.x + x >= 0)
	{
		basicObject::move(x, y);
	}
}
