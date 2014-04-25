#include "gameField.h"
#include <iostream>

gameField::gameField(SDL_Surface* SDLScreen)
{
    pSDLObjects = SDL_CreateRGBSurface(SDL_HWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    pSDLAnimatedLayer = SDL_CreateRGBSurface(SDL_HWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    this->pSDLScreen = SDLScreen;

    SDL_SetColorKey(pSDLObjects, SDL_SRCCOLORKEY, 0);
    SDL_SetColorKey(pSDLAnimatedLayer, SDL_SRCCOLORKEY, 0);

    this->playerObjects = new mainObjects;

    this->drawStarField();
    this->generateObjects();
}

gameField::~gameField()
{
	SDL_FreeSurface(this->pSDLObjects);
	SDL_FreeSurface(this->pSDLAnimatedLayer);
}

void gameField::generateObjects()
{
	playerPlatform* platform = new playerPlatform;
	this->playerObjects->platform = platform;
	this->objects.push_back(platform);

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			this->objects.push_back(new alienObject(60*i, j*60));
		}
	}
	
}

void gameField::makeFrame(std::vector<basicEvent*>* eventQueue)
{
	this->handleEvents(eventQueue);
	this->detectCollisions(eventQueue);
	this->processObjectsEvents(eventQueue);
	this->render();

	return;
}

void gameField::processObjectsEvents(std::vector<basicEvent*>* eventQueue)
{
	for (int i = 0; i < this->objects.size(); ++i)
	{
		if(this->objects[i] != NULL) this->objects[i]->handleEvents(eventQueue);
	}
	return;
}

void gameField::detectCollisions(std::vector<basicEvent*>* eventQueue)
{
	if(!this->playerObjects->bullet) return;
	for (int i = 0; i < this->objects.size(); ++i)
	{
		if(this->objects[i] == this->playerObjects->platform)continue;
		if(this->objects[i] == this->playerObjects->bullet)continue;
		if(
			this->playerObjects->bullet->getGeometry().y <= (this->objects[i]->getGeometry().y + 50) &&
			this->playerObjects->bullet->getGeometry().x >= (this->objects[i]->getGeometry().x) &&
			this->playerObjects->bullet->getGeometry().x <= (this->objects[i]->getGeometry().x + 50)
			)
		{
			eventQueue->push_back(new basicEvent(COLLISION, this->objects[i]));
		}
	}
}

void gameField::handleEvents(std::vector<basicEvent*>* eventQueue)
{
	for (auto i = 0; i < eventQueue->size(); ++i)
	{
		if(eventQueue->at(i)->event.type == SDL_KEYDOWN)
		{
			switch(eventQueue->at(i)->event.key.keysym.sym)
			{
				case SDLK_SPACE: this->createBullet(); break;
			}
		}
	}

	return;
}

void gameField::createBullet()
{
	if(!this->playerObjects->bullet)
	{
		basicObject* bullet = new bulletObject(this->playerObjects->platform);
		this->playerObjects->bullet = bullet;
		this->objects.push_back(bullet);
	}
}

void gameField::render()
{	
	SDL_FillRect(this->pSDLScreen, NULL, 0);
	SDL_FillRect(this->pSDLObjects, NULL, 0);

	this->renderStarLine();

	this->drawObjects(this->pSDLObjects);
	SDL_BlitSurface(this->pSDLObjects, NULL, this->pSDLScreen, NULL);
}

void gameField::drawObjects(SDL_Surface* pSDLObjects)
{
	std::vector<int> removedObjects;
	for (int i = 0; i < this->objects.size(); ++i)
	{
		if(this->objects[i] != NULL && this->objects[i]->draw(pSDLObjects)) 
		{
			if(this->objects[i] == this->playerObjects->bullet) this->playerObjects->bullet = NULL;
			removedObjects.push_back(i);
		}
	}

	for (int i = 0; i < removedObjects.size(); ++i)
	{
		delete this->objects[removedObjects[i]];
		this->objects.erase(this->objects.begin() + removedObjects[i]);
	}
	removedObjects.erase(removedObjects.begin(), removedObjects.end());
}

void gameField::renderStarLine()
{
	SDL_Rect r = {0, 1};
	SDL_BlitSurface(this->pSDLAnimatedLayer, NULL, this->pSDLObjects, &r);
	
	if(rand() % 100 > 50)
	{
		for (int i = 0; i < this->pSDLAnimatedLayer->w; ++i)
		{
			if(rand() % 200 == 7) this->drawRect(this->pSDLObjects, i, 0, 1, 1, 0xffffff);
		}
	}

	SDL_FillRect(this->pSDLAnimatedLayer, NULL, 0);
	SDL_BlitSurface(this->pSDLObjects, NULL, this->pSDLAnimatedLayer, NULL);
	SDL_BlitSurface(this->pSDLAnimatedLayer, NULL, this->pSDLScreen, NULL);
	SDL_FillRect(this->pSDLObjects, NULL, 0);
}

void gameField::drawStarField()
{
	for (int i = 0; i < this->pSDLAnimatedLayer->h; ++i)
	{
		if(rand() % 100 > 50)
		{
			for (int j = 0; j < this->pSDLAnimatedLayer->w; ++j)
			{
				if(rand() % 200 == 7) this->drawRect(this->pSDLAnimatedLayer, j, i, 1, 1, 0xffffff);
			}
		}
	}
}

void gameField::drawRect(SDL_Surface* screen, int x, int y, int width, int height, int color)
{
    SDL_Rect rect = {(Sint16)x, (Sint16)y, (Uint16)width, (Uint16)height};
    SDL_FillRect(screen, &rect, color);
}
