#include <SDL2/SDL.h>
#include "espion3d_structs.h"
#include <vector>

#include <iostream>
using namespace std;
#pragma once

void place_px(color rgba, coord2d xy, vector<point> *pixels)
{
	pixels->push_back({xy, rgba});
}

void clear_px(vector<point> *pixels, SDL_Renderer *renderer)
{
	pixels->clear();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void show_px(vector<point> pixels, SDL_Renderer *renderer, coord2d screen, int mode)
{
	// mode 1: normal y coordinates (+y = up)
	// mode 2: default, inverted y coordinates (+y = down)
	// screen: {width, height}
	for (point pixel : pixels)
	{

		SDL_SetRenderDrawColor(renderer, pixel.color.r, pixel.color.g, pixel.color.b, pixel.color.a);

		if (mode == 1)
		{
			SDL_RenderDrawPoint(renderer, pixel.pos.x, (screen.y / 2) - pixel.pos.y);
		}
		else if (mode == 2)
		{
			SDL_RenderDrawPoint(renderer, pixel.pos.x, pixel.pos.y);
		}
	}
	SDL_RenderPresent(renderer);
}
