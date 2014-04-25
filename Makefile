CC=g++
CFLAGS=-c -std=c++11 -O2 `sdl-config --cflags --libs` -lSDL_image -lSDL_ttf

all: space_invaders
	./space_invaders

space_invaders: main.o basicObject.o alienObject.o playerPlatform.o gameField.o events.o bulletObject.o space_invaders.o
	$(CC) -O2 `sdl-config --cflags --libs` -lSDL_image -lSDL_ttf -std=c++11 main.o basicObject.o alienObject.o playerPlatform.o gameField.o events.o bulletObject.o space_invaders.o -o space_invaders

basicObject.o: basicObject.cpp basicObject.h events.o
	$(CC) $(CFLAGS) basicObject.cpp

alienObject.o: alienObject.cpp alienObject.h basicObject.o
	$(CC) $(CFLAGS) alienObject.cpp

bulletObject.o: bulletObject.cpp bulletObject.h basicObject.o
	$(CC) $(CFLAGS) bulletObject.cpp

playerPlatform.o: playerPlatform.cpp playerPlatform.h basicObject.o
	$(CC) $(CFLAGS) playerPlatform.cpp

gameField.o: gameField.cpp gameField.h basicObject.o events.o playerPlatform.o bulletObject.o alienObject.o
	$(CC) $(CFLAGS) gameField.cpp

events.o: events.cpp events.h
	$(CC) $(CFLAGS) events.cpp

space_invaders.o: space_invaders.cpp space_invaders.h gameField.o
	$(CC) $(CFLAGS) space_invaders.cpp

main.o: main.cpp gameField.h screenSize.h
	$(CC) $(CFLAGS) main.cpp

clean:
	rm space_invaders *.o
