#include "screenSize.h"
#include "basicObject.h"

class bulletObject : public basicObject
{
	private:
		bool isExist;
	public:
		// void move(int, int);
		int draw(SDL_Surface*);
		void handleEvents(std::vector<basicEvent*>*);
		bulletObject(basicObject*);
};
