#include "olcPixelGameEngine.h"
#include <string>
#include <stdlib.h> 
#include <time.h> 

struct Point {
    int x = 0;
    int y = 0;
};

struct Pointf {
    float x = 0;
    float y = 0;
};

class Food {
public: 
    // This has to come from somewhere it's currently undefined
    olc::PixelGameEngine* pge;
    // This is the default constructor
    Food() = default;
    // It has to be passed on from poopies in order to have
    // otherwise the pointer is unasigned
    // This is a constructor
    Food(olc::PixelGameEngine* pge) {
        this->pge = pge;
    }
    
    Point food_loc;
    // These are defined before the constructor is called
    int cols; // pge->ScreenWidth() can't have something like this because pge is undefined
    int rows;
    int scale = 30;

    olc::Pixel foodColor = { 161, 255, 246 };

    
    void pickLocation()
    {
        srand(time(0));

        int cols = pge->ScreenWidth() / scale;
        int rows = pge->ScreenHeight() / scale;
        food_loc = { rand() % cols, rand() % rows };
    }

    void show()
    {
        //pge->FillRect((int)(food_loc.x)*scale, (int)(food_loc.y)*scale, scale, scale, foodColor);
        olc::Sprite* spriteFood = nullptr;
	    olc::Decal* decalFood = nullptr;
        spriteFood = new olc::Sprite("food.png");
        decalFood = new olc::Decal(spriteFood);
        //pickLocation();
        pge->DrawDecal( {(float)food_loc.x * scale, (float)food_loc.y * scale}, decalFood, {1.0f, 1.0f});

    }
};

class Snake {
public:
    olc::PixelGameEngine* pge;
    Snake() = default;
    Snake(olc::PixelGameEngine* pge) {
        this->pge = pge;
    }
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

    void update()
    {
        for (int i = 0; i < total - 1; i++)
        {
            tail[i] = tail[i + 1];
        }
        tail[total - 1] = { x , y  };

        x += speed * xDir; 
        y += speed * yDir;

        wrapAroundEdges(pge);
        //draws the score
        pge->DrawStringDecal({5, 5}, std::to_string(total), { 255, 175, 181 }, {4.0f, 4.0f});
    }
    void setDir(int x, int y)
    {
        xDir = x;
        yDir = y;
    }

    void keyboardInputs()
    {
        if(pge->GetKey(olc::Key::UP).bPressed)    { setDir(0, -1); return; }
        if(pge->GetKey(olc::Key::DOWN).bPressed)  { setDir(0, 1);  return; }
        if(pge->GetKey(olc::Key::RIGHT).bPressed) { setDir(1, 0);  return; } 
        if(pge->GetKey(olc::Key::LEFT).bPressed)  { setDir(-1, 0); return; }
    }

    void show()
    {
        //pge->FillRect(int(x)*scale, int(y)*scale, scale, scale, snakeColor);
        olc::Sprite* spriteHead = nullptr;
	    olc::Decal* decalHead = nullptr;
        spriteHead = new olc::Sprite("head2.png");
        decalHead = new olc::Decal(spriteHead);

        olc::Sprite* spriteSpine = nullptr;
	    olc::Decal* decalSpine = nullptr;
        spriteSpine = new olc::Sprite("spine.png");
        decalSpine = new olc::Decal(spriteSpine);

        pge->DrawDecal( {int(x)*scale, int(y)*scale}, decalHead, {1.0f, 1.0f});

        for (int i = 0; i < total; i++)
        {
           //pge->FillRect(int(tail[i].x)*scale, int(tail[i].y)*scale, scale, scale, snakeColor);
           pge->DrawDecal( {int(tail[i].x)*scale, int(tail[i].y)*scale}, decalSpine, {1.0f, 1.0f});
        }
    }

    int distance(Pointf a, Pointf b)
    {
        return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    }

    bool isEaten(Food& food)
    {
        int dist = distance({x, y}, {(float)(food.food_loc.x), (float)(food.food_loc.y)}); //distance between sneak and food
        if (dist < 1) { 
            total++; 
            //food.pickLocation();
            return true; 
        } else { 
            return false; 
        }
    }

    bool snakeDeath()
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

//private:
    void wrapAroundEdges(olc::PixelGameEngine* pge)
    {
        int width = pge->ScreenWidth() / scale;
        int height = pge->ScreenHeight() / scale;

        if (x > width) { x = 0; }
        if (x + 1 < 0) { x = width - 1; }
        if (y > height) { y = 0; }
        if (y + 1 < 0) { y = height - 1; }
    }

};

