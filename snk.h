#include "olcPixelGameEngine.h"
#include <string>

struct Point {
    int x = 0;
    int y = 0;
};

struct Pointf {
    float x = 0;
    float y = 0;
};

struct Rect {
    int width = 0;
    int height = 0;
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
        cols = pge->ScreenWidth() / scale;
        rows = pge->ScreenHeight() / scale;
    }
    int scale = 5;
    Point food_loc;
    // These are defined before the constructor is called
    int cols; // pge->ScreenWidth() can't have something like this because pge is undefined
    int rows;
    olc::Pixel foodColor = { 161, 255, 246 };

    void pickLocation()
    {
        food_loc = { rand() % cols, rand() % rows };
    }

    void show(olc::PixelGameEngine* pge)
    {
        pge->FillRect((int)(food_loc.x)*scale, (int)(food_loc.y)*scale, scale, scale, foodColor);
    }
};

class Snake {
public:
    int state = 1;
    float x = 0;
    float y = 0;
    float speed = 1;
    int scale = 5; //resolution
    int xDir = 1;
    int yDir = 0;
    int total = 0; 

    olc::Pixel snakeColor = { 252, 182, 223 };
    Pointf* tail = new Pointf[1000]; 

    void update(olc::PixelGameEngine* pge, Rect screen, int scale)
    {
        for (int i = 0; i < total - 1; i++)
        {
            tail[i] = tail[i + 1];
        }
        tail[total - 1] = { x , y  };

        x += speed * xDir; 
        y += speed * yDir;

        wrapAroundEdges(screen, scale);

        pge->DrawStringDecal({5, 5}, std::to_string(total), { 255, 255, 255 });
    }
    void setDir(int x, int y)
    {
        xDir = x;
        yDir = y;
    }

    void keyboardInputs(olc::PixelGameEngine* pge)
    {
        if(pge->GetKey(olc::Key::UP).bPressed)    { setDir(0, -1); return; }
        if(pge->GetKey(olc::Key::DOWN).bPressed)  { setDir(0, 1);  return; }
        if(pge->GetKey(olc::Key::RIGHT).bPressed) { setDir(1, 0);  return; } 
        if(pge->GetKey(olc::Key::LEFT).bPressed)  { setDir(-1, 0); return; }
    }

    void show(olc::PixelGameEngine* pge)
    {
        pge->FillRect(int(x)*scale, int(y)*scale, scale, scale, snakeColor);
        for (int i = 0; i < total; i++)
        {
           pge->FillRect(int(tail[i].x)*scale, int(tail[i].y)*scale, scale, scale, snakeColor);
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

private:
    void wrapAroundEdges(Rect& screen, int scale)
    {
        if (x > screen.width) { x = 0; }
        if (x + scale < 0) { x = screen.width - 1; }
        if (y > screen.height) { y = 0; }
        if (y + scale < 0) { y = screen.height - 1; }
    }

};

