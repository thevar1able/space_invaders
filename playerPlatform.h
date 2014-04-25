#include "screenSize.h"
#include "basicObject.h"

#define STEP 5

class playerPlatform : public basicObject
{
	private:
		int leftArrowPressed;
		int rightArrowPressed;
	public:
		void move(int, int);
		int draw(SDL_Surface*);
		void moveLeft(basicObject*);
		void moveRight(basicObject*);
		void handleEvents(std::vector<basicEvent*>*);
		playerPlatform();
};
