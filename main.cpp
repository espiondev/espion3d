#include <SDL.h>
#include <vector>
#include <iostream>
#include "sdl_stuff.h"
#include "px.h"
#include "triangle.h"
#include "line.h"
#pragma once

using namespace std;


int main(int argc, char* argv[]) {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(400, 400, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	vector<px> pxls = {};

	line({ 20, 100 }, { 50, 70 }, { 255, 255, 255, 255 }, renderer, &pxls);
	triangle({ 150, 150 }, { 20, 40 }, { 200, 160 }, { 255, 255, 255, 255 }, renderer, &pxls);
	show_px(pxls, renderer);

	bool running = true;
	SDL_Event ev;
	while (running)
	{

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				running = false;
		}
		SDL_UpdateWindowSurface(window);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

}