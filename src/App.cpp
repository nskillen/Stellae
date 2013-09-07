#include "App.h"

#include <iostream>
#include <cstdlib>

App* App::instance = NULL;

App::App() {
	initialized = false;
	done = false;
	window = NULL;
	renderer = NULL;
	last = 0;
}

void App::initSDL() {
	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		std::cerr<< "Error initializing SDL" << std::endl;
		std::cerr<< SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	window = SDL_CreateWindow("Test",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480,
		SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
	if(NULL == window) {
		std::cerr<< "Error creating SDL Window" << std::endl;
		std::cerr<< SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 
		SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if(NULL == renderer) {
		std::cerr<< "Error creating renderer" << std::endl;
		std::cerr<< SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	initialized = true;
}

void App::run() {
	App::instance = new App();
	App::instance->initSDL();
	if(App::instance->initialized) {
		App::instance->loop();
	}
}

void App::loop() {
	last = SDL_GetPerformanceCounter();
	std::list<Scene*>::iterator iter;
	while(!done) {
		iter = scenes.begin();
		if(scenes.end() == iter) {
			done = true;
		}
		while(iter != scenes.end()) {
			uint64_t cur = SDL_GetPerformanceCounter();
			double dt = (double)(cur-last)/SDL_GetPerformanceFrequency();
			(*iter)->tick(dt);
			(*iter)->render(renderer);
			iter++;
		}
	}
}