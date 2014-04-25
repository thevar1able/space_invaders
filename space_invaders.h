#include "gameField.h"

class space_invaders
{
	private:
		SDL_Surface* pSDLScreen;
		TTF_Font* pSDLFont;
		SDL_Event event;
		gameField* mainField;
		std::vector<basicEvent*> eventQueue;
		void mainLoop();
		bool checkExit();
		void eraseEventQueue();
		void pushEvent(eventTypes, SDL_Event);
	public:
		space_invaders();
		~space_invaders();
		void start();
};