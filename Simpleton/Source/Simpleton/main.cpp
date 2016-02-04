#include <stdio.h>
#include <time.h>

#include "./Game/GameManager.h"

int main(int argc, char* args[])
{
	// Seed rand
	srand ( (unsigned int)time(NULL) );

	char* APP_NAME = "My Game";
	int WIN_WIDTH = 1920;
	int WIN_HEIGHT = 1080;
	bool DEBUG_MODE = false;

	// Initialize and run the game
	GameManager game;
	game.Initialize(APP_NAME, WIN_WIDTH, WIN_HEIGHT, DEBUG_MODE);
	game.Update();
	game.Terminate();
	return 0;
}