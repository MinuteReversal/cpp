#include <iostream>
#include "Application.h"

#define SDL_MAIN_HANDLED

int main(int argc, char* argv[]) {
	Application app;
  app.loop();
	return 0;
}