#include "tetris_structs.h"
#include "esp_structs.h"
#include <iostream>
#pragma once
#include <vector>
using namespace std;

void square(coord2_s point1, coord2_s point2, color_s color, vector<point_s> *pixels)
{
    // interp for each y
    //      interp for each x

    // ensure point1 is higher than point 2
    if (point1.y < point2.y)
    {
        coord2_s temp;
        temp = point1;
        point1 = point2;
        point2 = temp;
    }
    {
        for (int y = point2.y; y <= point1.y; y++)
        {
            if (point1.x > point2.x)
            {
                for (int x = point2.x; x <= point1.x; x++)
                {
                    pixels->push_back(
                        {{x, y},
                         {color.r, color.g, color.b, color.a}});
                }
            }
            else
            {
                for (int x = point1.x; x <= point2.x; x++)
                {
                    pixels->push_back(
                        {{x, y},
                         {color.r, color.g, color.b, color.a}});
                }
            }
        }
    }
}

void draw_square_grid(coord2_s coord, color_s color, scene_info_s scene, vector<point_s> *pixels)
{
    /*
    coord: coordinates of the square
    color: color of the square
    screen dimensions: screen's width / height
    grid_numbers: how many squares fit in the width/how many squares fit in the height
    */
    coord2_s unit = {scene.dimensions.x / scene.grid.x, scene.dimensions.y / scene.grid.y};

    square({unit.x * (coord.x - 1), unit.y * (coord.y - 1)}, {unit.x * coord.x, unit.y * coord.y}, color, pixels);
}

void draw_piece(piece_s piece, scene_info_s scene, vector<point_s> *pixels)
{

    for (int y = 0; y < piece.piece_type.size(); y++)
    {
        for (int x = 0; x < piece.piece_type[y].size(); x++)
        {
            if (piece.piece_type[y][x] == true)
            {

                draw_square_grid({x + piece.pos.x, y + piece.pos.y}, piece.color, scene, &*pixels);
            }
        }
    }
}
piece_s rotate_piece(piece_s original)
{
    piece_s temp;
    temp.color = original.color;
    temp.pos = original.pos;

    // new height (old width)
    for (int i = 0; i < original.piece_type[0].size(); i++)
    {
        temp.piece_type.push_back({});
        // new width (old height)
        for (int m = 0; m < original.piece_type.size(); m++)
        {
            temp.piece_type[i].push_back(original.piece_type[original.piece_type.size() - 1 - m][i]);
        }
    }

    return temp;
}

void draw_all_pieces(vector<piece_s> pieces, scene_info_s scene, vector<point_s> *pixels)
{
    for (auto &pc : pieces)
    {
        draw_piece(pc, scene, pixels);
    }
}