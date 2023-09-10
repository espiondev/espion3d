
#include <vector>
#include "sdl_functions.h"
#include "triangle.h"
#include <cmath>
#include "misc_functions.h"
#include <iostream>
#include <stdio.h>
#include "espion3d_structs.h"
#include <SDL2/SDL.h>
using namespace std;

int main(int argc, char *argv[])
{

    // Define scene properties
    int mode = 2;
    coord2d dimensions = {800, 800};

    scene_info scene = {mode, dimensions};

    // Set up SDL window
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(scene.dimensions.x, scene.dimensions.y, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "espion3D");
    SDL_SetRenderDrawColor(renderer, 30, 40, 25, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    vector<point> pxls = {};
    triangle_filled({50, 90}, {280, 625}, {610, 420}, {0, 0, 0, 255}, &pxls);
    triangle_shaded(
        {{100, 150}, {255, 0, 0, 255}},
        {{300, 575}, {0, 255, 0, 255}},
        {{555, 420}, {0, 0, 255, 255}}, &pxls);

    triangle_wire({80, 130}, {290, 600}, {575, 420}, {255, 255, 255, 255}, &pxls);

    // line({0, 0}, {500, 400}, {0, 255, 0, 255}, &pxls);
    //  cout << vector_to_string(interpolate(250, 250, 500, 400)) << endl;
    show_px(pxls, renderer, dimensions, 2);
    SDL_UpdateWindowSurface(window);

    SDL_Event e;
    bool quit = false;
    int xMouse, yMouse;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
