#pragma once

#include <SDL.h>

class Scene {
public:
	virtual void tick(double) = 0;
	virtual void render(SDL_Renderer*) = 0;

	virtual ~Scene() { }
};