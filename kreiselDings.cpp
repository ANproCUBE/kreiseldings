//Italienische Spiralnudeln lieben diesen Trick!
//Orig: https://pr0gramm.com/top/4140917
//Auch noch: https://pr0gramm.com/new/3282451

#define OLC_PGE_APPLICATION
#include "engine.h"

struct punktElement{
	int x, y;
	double winkel;
};
punktElement elem[20];
int scrW, scrH;

class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "kreiselDings";
	}

public:
	bool OnUserCreate() override
	{
		scrW = ScreenWidth() / 2;
		scrH = ScreenHeight() / 2;

		for (int i = 0; i < 20; i++)
		{
			elem[i].winkel = 0.0;
			elem[i].x = 0;
			elem[i].y = 0;
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::WHITE); //Nach jedem Frame alten Content löschen

		for (int i = 1; i < 21; i++)
		{
			DrawCircle(scrW, scrH, i * 15, olc::BLACK); //20 Große Kreise zeichnen, 1. mit r=15
			elem[i-1].x = (sin(elem[i-1].winkel) * (i * 15)) + scrW;
			elem[i-1].y = (cos(elem[i-1].winkel) * (i * 15)) + scrH;
			FillCircle(elem[i-1].x, elem[i-1].y, 3, olc::RED); //Punkte auf den Kreisen zeichnen
			elem[i-1].winkel = elem[i-1].winkel + 0.01 + ((double)i/10000);
			//^ Hier den Winkel verändern, wenn die FPS zu hoch und die Drehung zu schnell ist
			//FPS-Unterschiede sind bei der jeweiligen Kompilierart sowie auf verschiedenen Systemen zu erwarten
		}

		for (int i = 0; i < 19; i++) //19 Linien zwischen den Punkten zeichnen
		{
			DrawLine(elem[i].x, elem[i].y, elem[i+1].x, elem[i+1].y, olc::RED);
		}

		return true;
	}
};

int main()
{
	Example demo;
	if (demo.Construct(1300, 700, 1, 1))
		demo.Start();

	return 0;
}
