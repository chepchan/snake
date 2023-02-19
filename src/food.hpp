#pragma once

#include "../libs/olcPixelGameEngine.h"
#include "utils.hpp"
class Food {
public: 
    olc::PixelGameEngine* pge;
    int cols;
    int rows;
    int scale = 30;
    Point food_loc;
    olc::Pixel foodColor = { 161, 255, 246 };

    Food() = default;
    Food(olc::PixelGameEngine* pge);
    
    void pickLocation();
    void show();

};