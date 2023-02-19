#pragma once

#include "food.hpp"
#include "../libs/olcPixelGameEngine.h"

#include <string>
#include <stdlib.h> 
#include <time.h> 
class Snake {
public:
    olc::PixelGameEngine* pge;
    int state = 1;
    float x = 0;
    float y = 0;
    float speed = 1;
    int scale = 30; //resolution
    int xDir = 1;
    int yDir = 0;
    int total = 0; 
    olc::Pixel snakeColor = { 255, 175, 181 }; //252, 182, 223
    Pointf* tail = new Pointf[1000]; 

    Snake() = default;
    Snake(olc::PixelGameEngine* pge);

    void update();
    void setDir(int x, int y);
    void keyboardInputs();
    void show();
    int distance(Pointf a, Pointf b);
    bool isEaten(Food& food);
    bool snakeDeath();
    void wrapAroundEdges();
};

