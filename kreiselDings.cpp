/*
Italienische Spiralnudeln lieben diesen Trick!
Orig: https://pr0gramm.com/top/4140917
Auch noch: https://pr0gramm.com/new/3282451


DANK GEHT RAUS AN Lett1 & cxii
1A Ehrenmänner/innen!

Fix FPS-dependency:
angle += speed * deltaTime
deltaTime is the time between the previous frame and the current one
*/

#define OLC_PGE_APPLICATION
#include "engine.h"

struct punktElement{
	int x, y;
	double winkel;
};
punktElement elem[20];
int scrW, scrH;
double speed;

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
		speed = 10;
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
			DrawCircle(scrW, scrH, i * 15, olc::BLACK); //Große Kreise zeichnen, 1. mit r=15
			elem[i-1].x = (cos(elem[i-1].winkel) * (i * 15)) + scrW;
			elem[i-1].y = (sin(elem[i-1].winkel) * (i * 15)) + scrH;
			FillCircle(elem[i-1].x, elem[i-1].y, 3, olc::RED); //Punkte auf den Kreisen zeichnen
			elem[i-1].winkel += ((double)i/speed) * fElapsedTime; //Den Winkel FPS-unabhängig berechnen - 10 = speed
		}
		
		for (int i = 0; i < 19; i++) //19 Linien zwischen den Punkten zeichnen
			DrawLine(elem[i].x, elem[i].y, elem[i+1].x, elem[i+1].y, olc::RED);

		if (1)
		{
			DrawLine(scrW - 20 * 15, scrH, scrW + 20 * 15, scrH, olc::BLACK); //Crosshair horizontal
			DrawLine(scrW, scrH - 20 * 15, scrW, scrH + 20 * 15, olc::BLACK); //Crosshair vertikal
		}

		if (GetKey(olc::Key::LEFT).bHeld)
			speed -= 0.01;
		else if (GetKey(olc::Key::RIGHT).bHeld)
			speed += 0.01;

		DrawString(0, 0, "Speed: " + std::to_string(speed), olc::BLACK);
		DrawString(0, 10, "01. Winkel: " + std::to_string((elem[0].winkel*360)/(2*3.14159)) + "Grad", olc::BLACK);
		DrawString(0, 20, "20. Winkel: " + std::to_string((elem[19].winkel*360)/(2*3.14159)) + "Grad", olc::BLACK);
		return true;
	}
};

int main()
{
	Example demo;
	if (demo.Construct(1400, 800, 1, 1))
		demo.Start();

	return 0;
}
