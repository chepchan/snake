#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

using namespace std::chrono_literals; //for sleep

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

class Worm {
    public:
    float x = 0;
    float y = 0;
    float speed = 1;
    int xDir = 1;
    int yDir = 0;
    float deltaTime;
    int total = 0; //making the snake longer
    Pointf* tail = new Pointf[100]; 
    void update(Rect screen, int scale)
    {
        for (int i = 0; i < total - 1; i++)
        {
            tail[i] = tail[i + 1];
        }
        tail[total - 1] = (Pointf){ x , y  };

        x += speed * xDir; //*scale
        y += speed * yDir; //*scale but it makes it way too fast
        wrapAroundEdges(screen, scale);
    }
    void directionOfMovement(int x, int y)
    {
        xDir = x;
        yDir = y;
    }

    private:
    void wrapAroundEdges(Rect& screen, int scale)
    {
        if (x > screen.width) { x = 0; }
        if (x + scale < 0) { x = screen.width - scale; }
        if (y > screen.height) { y = 0; }
        if (y + scale < 0) { y = screen.height - scale; }
    }
};

class POOPIES : public olc::PixelGameEngine
{
private:
    int scale = 5; //resolution
    Worm smolWorm;
    Point yum;
    int cols = ScreenWidth() / scale;
    int rows = ScreenHeight() / scale;
    olc::Pixel babyPink = { 255, 161, 203 };
    olc::Pixel purple = { 194, 115, 255 };

public:
	POOPIES() { sAppName = "POOPIES"; }

    void keyboardInputs()
    {
        if     (GetKey(olc::Key::UP).bPressed)    { smolWorm.directionOfMovement(0, -1); }
        else if(GetKey(olc::Key::DOWN).bPressed)  { smolWorm.directionOfMovement(0, 1); }
        else if(GetKey(olc::Key::RIGHT).bPressed) { smolWorm.directionOfMovement(1, 0); } 
        else if(GetKey(olc::Key::LEFT).bPressed)  { smolWorm.directionOfMovement(-1, 0); }
    }

    void showPredator()
    {
        FillRect(int(smolWorm.x)*scale, int(smolWorm.y)*scale, scale, scale, babyPink);
        for (int i = 0; i < smolWorm.total; i++)
        {//SMOLWORM.TAIL[I].X   &   SMOLWORM.TAIL[I].Y   ???
           FillRect(int(smolWorm.tail[i].x)*scale, int(smolWorm.tail[i].y)*scale, scale, scale, babyPink);
        }
    }

    void pickLocationYum()
    {
        yum = { rand() % cols, rand() % rows };
    }

    void showYum()
    {
        //food = location
        FillRect(int(yum.x)*scale, int(yum.y)*scale, scale, scale, purple);
    }

    int distance(int x1, int y1, int x2, int y2)
    {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

    bool yumIsEaten()
    {
        int dist = distance(smolWorm.x, smolWorm.y, yum.x, yum.y); //distance between sneak and food
        if (dist < 1) { 
            smolWorm.total++; 
            return true; 
        } else { 
            return false; 
        }
    }
    
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float deltaTime) override
	{
        Clear(olc::Pixel(0, 0, 0));
        std::this_thread::sleep_for(50ms); //sleep
        
		smolWorm.update({cols, rows}, scale);
        showPredator(); 
        keyboardInputs();

        showYum();
        if (yumIsEaten()) pickLocationYum();

		return true;
	}
};

int main()
{
	POOPIES demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();

	return 0;
}