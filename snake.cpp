#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "snk.h"

using namespace std::chrono_literals;

class POOPIES : public olc::PixelGameEngine
{
    Worm smolWorm;
	Food tasty;
	//bool over = false;

public:
	POOPIES() { sAppName = "POOPIES"; }

	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float deltaTime) override
	{
        Clear(olc::Pixel(0, 0, 0));
        std::this_thread::sleep_for(50ms); //sleep

		smolWorm.update({tasty.cols, tasty.rows}, smolWorm.scale);
        smolWorm.showPredator(this); 
        smolWorm.keyboardInputs(this);

        tasty.showYum(this);
        if (smolWorm.yumIsEaten(tasty)) tasty.pickLocationYum();

		smolWorm.DIEDIEDIE();   
		smolWorm.gameOverStolen(this);   // game pover only appears for 1 frame at a time
		//if (smolWorm.DIEDIEDIE()) { smolWorm.gameOverStolen(this); }
 
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