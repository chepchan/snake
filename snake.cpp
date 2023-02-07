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

	void gameOverStolen() //only appears for 1 frame 
    {
        if(smolWorm.game == 2)
        {
            Pointf death;
            olc::Sprite* spriteGameOver = nullptr;
	        olc::Decal* decalGameOver = nullptr;

            spriteGameOver = new olc::Sprite("badKitty.png");
            decalGameOver = new olc::Decal(spriteGameOver);

			death.x = (ScreenWidth() / 2) - (decalGameOver->sprite->width / 2);
			death.y = (ScreenHeight() / 2) - (decalGameOver->sprite->height / 2);

			DrawDecal( {death.x, death.y}, decalGameOver, {1.0f, 1.0f} );

        }else return;
    }

	void gaming()
	{
		smolWorm.update({tasty.cols, tasty.rows}, smolWorm.scale);
        smolWorm.showPredator(this); 
        smolWorm.keyboardInputs(this);

        tasty.showYum(this);
        if (smolWorm.yumIsEaten(tasty)) tasty.pickLocationYum();

		smolWorm.DIEDIEDIE();   
	}

	void gameOver()
	{
		smolWorm.DIEDIEDIE();   
		gameOverStolen();   // game over only appears for 1 frame at a time
	}

public:
	POOPIES() { 
        sAppName = "POOPIES"; 
        tasty = Food(this);
    }

	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float deltaTime) override
	{
        Clear(olc::Pixel(101, 101, 101));
        std::this_thread::sleep_for(50ms); //sleep

		switch(smolWorm.game)
		{
			case 1: gaming(); break;
			case 2: gameOver(); break;
		}

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