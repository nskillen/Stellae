#pragma once

#include <list>

#include <GLXW/glxw.h>
#include <SDL.h>

#include "Scene.h"

class App {
public:
	static void run();
private:
	App();

	void initSDL();
	void loop();

	static App* instance;

	bool initialized, done;
	uint64_t last;

	SDL_Window *window;
	SDL_Renderer *renderer;

	std::list<Scene*> scenes;
};
