#include "olcPixelGameEngine.h"

struct Point {
    int x = 0;
    int y = 0;
};

struct Pointf {
    float x = 0;
    float y = 0;
};
//int distance(Pointf a, Pointf b);

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
    int total = 0; //making the snake longer
    Pointf* tail = new Pointf[100]; 
    void update(Rect screen, int scale)
    {
        for (int i = 0; i < sizeof(tail) - 1; i++)
        {
            tail[i] = tail[i + 1];
        }
        tail[total - 1] = (Pointf){ x , y  };

        x += speed * xDir; //*scale
        y += speed * yDir; //*scale but it makes it way too fast
        wrapAroundEdges(screen, scale);
    }
    void setDir(int x, int y)
    {
        xDir = x;
        yDir = y;
    }
	// void DIEDIEDIE()
	// {
	// 	for (int i = 0; i < sizeof(tail); i++)
	// 	{
	// 		Pointf position = tail[i];
	// 		int d = distance(position);
	// 	}
	// }

    private:
    void wrapAroundEdges(Rect& screen, int scale)
    {
        if (x > screen.width) { x = 0; }
        if (x + scale < 0) { x = screen.width - 1; }
        if (y > screen.height) { y = 0; }
        if (y + scale < 0) { y = screen.height - 1; }
    }

};