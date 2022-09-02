#include "px.h"
#include <vector>
#include <SDL.h>
using namespace std;
#pragma once

void place_px(vector<int> rgba, vector<int> xy, vector<px>* pixels)
{
	pixels->push_back({ rgba, xy });
}

void clear_px(vector<px>* pixels)
{
	pixels->clear();
}

void show_px(vector<px> pixels, SDL_Renderer* renderer, vector<int> screen)
{
	// screen: {width, height}
	vector<int> rgba;
	for (px pixel : pixels) {

		if (pixel.rgba != rgba)
		{
			rgba = pixel.rgba;
			SDL_SetRenderDrawColor(renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
		}

		SDL_RenderDrawPoint(renderer, (screen[0] / 2) + pixel.xy[0], (screen[1] / 2) - pixel.xy[1]);

	}
	SDL_RenderPresent(renderer);
}
