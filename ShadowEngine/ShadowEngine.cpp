// ShadowEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

GfxKey lt = 0;
GfxKey ct = 0;

GfxKey lm = 0;
GfxKey lmdraw = 0;
GfxKey lmscreen = 0;

int lmWidth = 512, lmHeight = 512;
int lmHalfWidth = lmWidth*0.5f, lmHalfHeight = lmHeight*0.5f;
int screenWidth = 1920, screenHeight = 1080;

struct Wall
{
	float x1, y1;
	float x2, y2;

	Wall() {}
	Wall(float x1, float y1, float x2, float y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
};

#define wallCount 8
Wall walls[wallCount] = {
	/*{500,100, 600,200},
	{600,200, 600,300},
	{600,400, 700,400},
	{700,400, 700,600},*/
	{400,400, 700,400},
	{700,400, 700,500},
	{700,500, 400,500},
	{400,500, 400,400},

	{800,400, 1100,400},
	{1100,400, 1100,500},
	{1100,500, 800,500},
	{800,500, 800,400}
};

class AppClass {
public:
	bool GfxMain(GfxWrap &wrap) {
		return true;
	}
};

static bool GfxMain(GfxWrap &wrap) {
	static double ang = 45.0;
	GfxVector2i mp = wrap.GetMousePos();
	GfxVector2i lmHalfSize(lmHalfWidth, lmHalfHeight);
	GfxVector2i lmTopLeft = mp - lmHalfSize;

	ang += 1.0;
	wrap.Clear(GfxColor(255,255,255,0));

	wrap.SetTarget(lmdraw);
	wrap.Clear();
	wrap.BlitEx(lm, 0.0f, 0.0f, lmWidth, lmHeight, 0,0,0,1,GfxBlendNone);
	//wrap.DrawTriangle(0, 0, 0, 100, 100, 100, GfxColor(255, 0, 0));
	//wrap.DrawQuad(320, 160, 224, 320, 448, 1280, 640, 320, GfxColor(255, 0, 0));
	//wrap.DrawQuad(112,192, 192,144, 384,288, 224,384, GfxColor(0, 0, 0));

	Wall convertedWalls[wallCount];

	for (int i = 0; i < wallCount; i++)
	{
		convertedWalls[i].x1 = walls[i].x1 - lmTopLeft.x;
		convertedWalls[i].y1 = walls[i].y1 - lmTopLeft.y;
		convertedWalls[i].x2 = walls[i].x2 - lmTopLeft.x;
		convertedWalls[i].y2 = walls[i].y2 - lmTopLeft.y;

		/*wrap.DrawTriangle(
			convertedWalls[i].x1, convertedWalls[i].y1
			, convertedWalls[i].x2, convertedWalls[i].y2
			, lmHalfWidth, lmHalfHeight
			, GfxColor(0,0,0)
		);*/
		float quadScalar = 20.f;
		wrap.DrawQuad(
			convertedWalls[i].x1, convertedWalls[i].y1
			, convertedWalls[i].x2, convertedWalls[i].y2
			, quadScalar*(convertedWalls[i].x2-lmHalfWidth)+lmHalfWidth, quadScalar*(convertedWalls[i].y2 - lmHalfHeight) + lmHalfHeight
			, quadScalar*(convertedWalls[i].x1 - lmHalfWidth) + lmHalfWidth, quadScalar*(convertedWalls[i].y1 - lmHalfHeight) + lmHalfHeight
			, GfxColor(0, 0, 0)
		);
	}


	wrap.Present();

	wrap.SetTarget(lmscreen);
	wrap.Clear();
	//wrap.BlitEx(lmdraw, 0.0f, 0.0f, 256.0f, 256.0f, 0, 0, 0, 1, GfxBlendAdd);
	wrap.BlitEx(lmdraw, (float)mp.x-lmHalfWidth, (float)mp.y-lmHalfHeight, lmWidth, lmHeight, 0, 0, 0, 1.f, GfxBlendAdd);
	wrap.Present();

	wrap.UnsetTarget();
	wrap.BlitEx(lt, 0, 0, screenWidth, screenHeight, 0, 0, 0, 1, 1.f, GfxBlendNone);
	wrap.BlitEx(lmscreen, 0, 0, screenWidth, screenHeight, 0, 0, 0, 1, GfxBlendMod);


	//OutputDebugStringA("test");
	return true;
}

//int main()
//[](GfxWrap &wrap) {wrap.Clear(GfxColor(90, 0, 20, 0)); return true; }
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	AppClass app;
	GfxWrap gfx;

	gfx.Init("test", screenWidth, screenHeight, GfxMain);
	//gfx.Init("test", 1024, 768, [&app](GfxWrap& wrap) {return app.GfxMain(wrap); });
	lt = gfx.LoadTexture("c:/Media/metal_1024.png");
	//ct = gfx.CreateTexture(512, 512);

	lm = gfx.LoadTexture("c:/Media/lightmap_512_dim_incand.png");
	lmdraw = gfx.CreateTexture(lmWidth, lmHeight);
	lmscreen = gfx.CreateTexture(screenWidth, screenHeight);

	gfx.Begin();

}
