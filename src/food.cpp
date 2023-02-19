#include "food.hpp"

Food::Food(olc::PixelGameEngine* pge) {
    this->pge = pge;
}

void Food::pickLocation()
{
    srand(time(0));
    int cols = pge->ScreenWidth() / scale;
    int rows = pge->ScreenHeight() / scale;
    food_loc = { rand() % cols, rand() % rows };
}

void Food::show()
{
    olc::Sprite* spriteFood = nullptr;
    olc::Decal* decalFood = nullptr;
    spriteFood = new olc::Sprite("assets/food.png");
    decalFood = new olc::Decal(spriteFood);

    pge->DrawDecal( {(float)food_loc.x * scale, (float)food_loc.y * scale}, decalFood, {1.0f, 1.0f});
}