// ShadowEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

GfxKey lt = 0;
GfxKey ct = 0;

GfxKey lm = 0;
GfxKey lmdraw = 0;
GfxKey lmscreen = 0;

class AppClass {
public:
	bool GfxMain(GfxWrap &wrap) {
		return true;
	}
};

static bool GfxMain(GfxWrap &wrap) {
	static double ang = 45.0;
	GfxVector2i mp = wrap.GetMousePos();

	ang += 1.0;
	wrap.Clear(GfxColor(255,255,255,0));

	wrap.SetTarget(lmdraw);
	wrap.Clear();
	wrap.BlitEx(lm, 0.0f, 0.0f, 256.0f, 256.0f, 0,0,0,1,GfxBlendNone);
	wrap.DrawTriangle(0, 0, 0, 100, 100, 100, GfxColor(255, 0, 0));
	wrap.Present();

	wrap.SetTarget(lmscreen);
	wrap.Clear();
	wrap.BlitEx(lmdraw, 0.0f, 0.0f, 256.0f, 256.0f, 0, 0, 0, 1, GfxBlendAdd);
	wrap.BlitEx(lmdraw, mp.x, mp.y, 512.0f, 512.0f, 0, 0, 0, 1, GfxBlendAdd);
	wrap.Present();

	wrap.UnsetTarget();
	wrap.BlitEx(lt, 0, 0, 1024, 768, 0, 0, 0, 1, GfxBlendNone);
	wrap.BlitEx(lmscreen, 0, 0, 1024, 768, 0, 0, 0, 1, GfxBlendMod);


	//OutputDebugStringA("test");
	return true;
}

//int main()
//[](GfxWrap &wrap) {wrap.Clear(GfxColor(90, 0, 20, 0)); return true; }
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	AppClass app;
	GfxWrap gfx;

	gfx.Init("test", 1024, 768, GfxMain);
	//gfx.Init("test", 1024, 768, [&app](GfxWrap& wrap) {return app.GfxMain(wrap); });
	lt = gfx.LoadTexture("c:/Media/metal_1024.png");
	//ct = gfx.CreateTexture(512, 512);

	lm = gfx.LoadTexture("c:/Media/lightmap_256.png");
	lmdraw = gfx.CreateTexture(256, 256);
	lmscreen = gfx.CreateTexture(1024, 768);

	gfx.Begin();

}
