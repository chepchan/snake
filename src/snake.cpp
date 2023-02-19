#include "snake.hpp"

Snake::Snake(olc::PixelGameEngine* pge) {
    this->pge = pge;
}

void Snake::update()
{
    for (int i = 0; i < total - 1; i++)
    {
        tail[i] = tail[i + 1];
    }
    tail[total - 1] = { x , y  };
    x += speed * xDir; 
    y += speed * yDir;
    wrapAroundEdges(pge);
    pge->DrawStringDecal({5, 5}, std::to_string(total), { 255, 175, 181 }, {4.0f, 4.0f});
}

void Snake::setDir(int x, int y)
{
    xDir = x;
    yDir = y;
}

void Snake::keyboardInputs()
{
    if(pge->GetKey(olc::Key::UP).bPressed)    { setDir(0, -1); return; }
    if(pge->GetKey(olc::Key::DOWN).bPressed)  { setDir(0, 1);  return; }
    if(pge->GetKey(olc::Key::RIGHT).bPressed) { setDir(1, 0);  return; } 
    if(pge->GetKey(olc::Key::LEFT).bPressed)  { setDir(-1, 0); return; }
}

void Snake::show()
{
    olc::Sprite* spriteHead = nullptr;
    olc::Decal* decalHead = nullptr;
    spriteHead = new olc::Sprite("assets/head2.png");
    decalHead = new olc::Decal(spriteHead);
    olc::Sprite* spriteSpine = nullptr;
    olc::Decal* decalSpine = nullptr;
    spriteSpine = new olc::Sprite("assets/spine.png");
    decalSpine = new olc::Decal(spriteSpine);
    pge->DrawDecal( {int(x)*scale, int(y)*scale}, decalHead, {1.0f, 1.0f});
    for (int i = 0; i < total; i++)
    {
       pge->DrawDecal( {int(tail[i].x)*scale, int(tail[i].y)*scale}, decalSpine, {1.0f, 1.0f});
    }
}

int Snake::distance(Pointf a, Pointf b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

bool Snake::isEaten(Food& food)
{
    int dist = distance({x, y}, {(float)(food.food_loc.x), (float)(food.food_loc.y)});
    if (dist < 1) { 
        total++; 
        return true; 
    } else { 
        return false; 
    }
}

bool Snake::snakeDeath()
{
	for (int i = 0; i < total - 1; i++)
	{
		Pointf position = tail[i];
		int d = distance({x, y}, {tail[i].x, tail[i].y});
        if (d < 1)
        {
            state = 2;
            return true;
        }
	}
    return false;
}

void Snake::wrapAroundEdges(olc::PixelGameEngine* pge)
{
    int width = pge->ScreenWidth() / scale;
    int height = pge->ScreenHeight() / scale;
    if (x > width) { x = 0; }
    if (x + 1 < 0) { x = width - 1; }
    if (y > height) { y = 0; }
    if (y + 1 < 0) { y = height - 1; }
}