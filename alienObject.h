#include "basicObject.h"

class alienObject : public basicObject
{
	private:
		bool isExist;
	public:
		void move(int, int);
		void handleEvents(std::vector<basicEvent*>*);
		int draw(SDL_Surface*);
		alienObject(int, int);
};
