#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <string>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "snk.h"

using namespace std::chrono_literals;
class POOPIES : public olc::PixelGameEngine
{
    Worm smolWorm;
	Food tasty;

	void gameOverStolen()
    {
        if(smolWorm.game == 2)
        {
            Pointf gameOverDecal;
			Pointf tryAgainDecal;
			// Pointf finalScoreDecal;

            olc::Sprite* spriteGameOver = nullptr;
	        olc::Decal* decalGameOver = nullptr;

            spriteGameOver = new olc::Sprite("badKitty.png");
            decalGameOver = new olc::Decal(spriteGameOver);

			gameOverDecal.x = (ScreenWidth() / 2) - (decalGameOver->sprite->width / 2);
			gameOverDecal.y = (ScreenHeight() / 2) - (decalGameOver->sprite->height / 2);
			DrawDecal( {gameOverDecal.x, gameOverDecal.y}, decalGameOver, {1.0f, 1.0f} );

			tryAgainDecal.x = gameOverDecal.x - 40;
			tryAgainDecal.y = gameOverDecal.y + 130;
			DrawStringDecal({tryAgainDecal.x, tryAgainDecal.y}, "Press enter to try again", { 255, 255, 255 });

			// finalScoreDecal.x = gameOverDecal.x + 130;
			// finalScoreDecal.y = gameOverDecal.y - 130;
			DrawStringDecal({5, 5}, std::to_string(smolWorm.scoreTrack), { 255, 255, 255 });

			if(GetKey(olc::Key::ENTER).bPressed)
			{
				smolWorm.scoreTrack = 0;
				smolWorm.game = 1;
				return;
			}

        }else return;
    }

	void gaming()
	{
		smolWorm.update(this, {tasty.cols, tasty.rows}, smolWorm.scale);
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
        Clear(olc::Pixel(0, 0, 0));
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