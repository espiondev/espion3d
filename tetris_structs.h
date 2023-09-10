#include "esp_structs.h"
#include <vector>
#pragma once
using namespace std;
struct square_s
{
    bool taken = false;
    coord2_s pos;
    color_s color;
};
const vector<vector<bool>> L_spaces =
    {
        {true, false},
        {true, false},
        {true, true}};

const vector<vector<bool>> SQUARE_spaces =
    {
        {true, true},
        {true, true}};

const vector<vector<bool>> T_spaces =
    {
        {true, true, true},
        {false, true, false}};

const vector<vector<bool>> ZIGZAG_spaces =
    {
        {true, false},
        {true, true},
        {false, true}};

const vector<vector<bool>> LINE_spaces =
    {
        {true},
        {true},
        {true},
        {true}};

struct piece_s
{
    vector<vector<bool>> piece_type;
    color_s color;
    coord2_s pos;
};