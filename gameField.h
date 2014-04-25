#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <stdlib.h>

#include "events.h"
#include "basicObject.h"
#include "screenSize.h"
#include "playerPlatform.h"
#include "bulletObject.h"
#include "alienObject.h"

struct mainObjects
{
	basicObject* platform = NULL;
	basicObject* bullet = NULL;
};

class gameField : public basicObject
{
	private:
		SDL_Event event;
		SDL_Surface* pSDLScreen;
		SDL_Surface* pSDLObjects;
		SDL_Surface* pSDLAnimatedLayer;
		std::vector<basicObject*> objects;
		mainObjects* playerObjects;
		void render();
		void renderStarLine();
		void drawStarField();
		void drawRect(SDL_Surface*, int, int, int, int, int);
		void drawObjects(SDL_Surface*);
		void processObjectsEvents(std::vector<basicEvent*>*);
		void generateObjects();
		void createBullet();
		void detectCollisions(std::vector<basicEvent*>*);
		void handleEvents(std::vector<basicEvent*>*);
		inline void destroyObject(basicObject*);
	public:
		gameField(SDL_Surface*);
		~gameField();
		void makeFrame(std::vector<basicEvent*>*);
};