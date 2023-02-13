#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <string>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "snk.h"

using namespace std::chrono_literals;
class SNAKEGAME : public olc::PixelGameEngine
{
    Snake snake;
	Food food;

	void gameOverScreen()
    {
        if(snake.state == 2)
        {
            Pointf gameOverDecal;
			Pointf tryAgainDecal;

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

			DrawStringDecal({5, 5}, std::to_string(snake.total), { 255, 255, 255 });

			if(GetKey(olc::Key::ENTER).bPressed)
			{
				snake.total = 0;
				snake.state = 1;
				return;
			}

        }else return;
    }

	void gameBegin()
	{
		snake.update(this, {food.cols, food.rows}, snake.scale);
        snake.keyboardInputs(this);
        snake.show(this); 

        food.show(this);
        if (snake.isEaten(food)) food.pickLocation();

		snake.snakeDeath();   
	}

	void gameEnd()
	{
		snake.snakeDeath();   
		gameOverScreen(); 
	}

public:
	SNAKEGAME() { 
        sAppName = "SNAKE"; 
        food = Food(this);
    }

	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float deltaTime) override
	{
        Clear(olc::Pixel(0, 0, 0));
        std::this_thread::sleep_for(50ms); //sleep

		switch(snake.state)
		{
			case 1: gameBegin(); break;
			case 2: gameEnd(); break;
		}

		return true;
	}
};

int main()
{
	SNAKEGAME game;
    const int width = 256;
    const int height = 240;
    const int pixelScale = 4;

	if (!game.Construct(width, height, pixelScale, pixelScale)) return EXIT_FAILURE;

	game.Start();

	return EXIT_SUCCESS;
}