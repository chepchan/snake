#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "snk.h"

using namespace std::chrono_literals; //for sleep

// struct Point {
//     int x = 0;
//     int y = 0;
// };

// struct Pointf {
//     float x = 0;
//     float y = 0;
// };
// int distance(Pointf a, Pointf b);

// struct Rect {
//     int width = 0;
//     int height = 0;
// };

// class Worm {
//     public:
//     float x = 0;
//     float y = 0;
//     float speed = 1;
//     int xDir = 1;
//     int yDir = 0;
//     int total = 0; //making the snake longer
//     Pointf* tail = new Pointf[100]; 
//     void update(Rect screen, int scale)
//     {
//         for (int i = 0; i < sizeof(tail) - 1; i++)
//         {
//             tail[i] = tail[i + 1];
//         }
//         tail[total - 1] = (Pointf){ x , y  };

//         x += speed * xDir; //*scale
//         y += speed * yDir; //*scale but it makes it way too fast
//         wrapAroundEdges(screen, scale);
//     }
//     void setDir(int x, int y)
//     {
//         xDir = x;
//         yDir = y;
//     }
// 	// void DIEDIEDIE()
// 	// {
// 	// 	for (int i = 0; i < sizeof(tail); i++)
// 	// 	{
// 	// 		Pointf position = tail[i];
// 	// 		int d = distance(position);
// 	// 	}
// 	// }

//     private:
//     void wrapAroundEdges(Rect& screen, int scale)
//     {
//         if (x > screen.width) { x = 0; }
//         if (x + scale < 0) { x = screen.width - 1; }
//         if (y > screen.height) { y = 0; }
//         if (y + scale < 0) { y = screen.height - 1; }
//     }

// };

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
        if(GetKey(olc::Key::UP).bPressed)    { smolWorm.setDir(0, -1); return; }
        if(GetKey(olc::Key::DOWN).bPressed)  { smolWorm.setDir(0, 1);  return; }
        if(GetKey(olc::Key::RIGHT).bPressed) { smolWorm.setDir(1, 0);  return; } 
        if(GetKey(olc::Key::LEFT).bPressed)  { smolWorm.setDir(-1, 0); return; }
    }

    void showPredator()
    {
        FillRect(int(smolWorm.x)*scale, int(smolWorm.y)*scale, scale, scale, babyPink);
        for (int i = 0; i < smolWorm.total; i++)
        {
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

    int distance(Pointf a, Pointf b)
    {
        return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    }

    bool yumIsEaten()
    {
        int dist = distance({smolWorm.x, smolWorm.y}, {yum.x, yum.y}); //distance between sneak and food
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
	POOPIES game;
    const int width = 256;
    const int height = 240;
    const int pixelScale = 4;

	if (!game.Construct(width, height, pixelScale, pixelScale)) return EXIT_FAILURE;

	game.Start();

	return EXIT_SUCCESS;
}