#include "space_invaders.h"

space_invaders::space_invaders()
{
	SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetCaption("Yet another shitty game", NULL);
    SDL_EnableKeyRepeat(0, SDL_DEFAULT_REPEAT_INTERVAL);
    this->pSDLScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);

    TTF_Init();
    this->pSDLFont = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSansMono.ttf", 25);

    this->mainField = new gameField(pSDLScreen);
}

space_invaders::~space_invaders()
{
	TTF_CloseFont(this->pSDLFont);
	TTF_Quit();

	SDL_Quit();
}

void space_invaders::start()
{
	this->mainLoop();
}

void space_invaders::mainLoop()
{
	bool quit = false;
	int ticks, delta_ticks, delay_time;

	while(!quit)
	{
		ticks = SDL_GetTicks();

		while( SDL_PollEvent(&this->event) )
		{
			if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
			{
				this->pushEvent(SDL, event);
			}
		}
		
		quit = this->checkExit();

		mainField->makeFrame(&this->eventQueue);

		this->eraseEventQueue();

		SDL_Flip(this->pSDLScreen);
		delta_ticks = SDL_GetTicks() - ticks;
		delay_time = (1000/90) - delta_ticks;

		if(delay_time > 0) SDL_Delay(delay_time);
	}

	return;
}

void space_invaders::pushEvent(eventTypes eventType, SDL_Event event)
{
	this->eventQueue.push_back(new basicEvent(eventType, event));
}

void space_invaders::eraseEventQueue()
{
	for (auto i = 0; i < this->eventQueue.size(); ++i)
	{
		delete this->eventQueue[i];
	}
	this->eventQueue.erase(this->eventQueue.begin(), this->eventQueue.end());
}

bool space_invaders::checkExit()
{
	if(this->eventQueue.size())
	{
		SDL_Event tempEvent = this->eventQueue.back()->event;
		if(tempEvent.type == SDL_KEYDOWN && tempEvent.key.keysym.sym == SDLK_ESCAPE)
		{
			return true;
		}
	}
	return false;
}