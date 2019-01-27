// ShadowEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

GfxKey lt = 0;
GfxKey ct = 0;

static bool GfxMain(GfxWrap &wrap) {
	static double ang = 45.0;

	ang += 1.0;
	wrap.Clear(GfxColor(20,90,20,0));

	wrap.SetTarget(lt);
	wrap.DrawTriangle(100, 100, 100, 0, 0, 100, GfxColor(0, 0, 0));
	wrap.UnsetTarget();
	wrap.BlitEx(lt, 300,300,400,400, 200, 200, ang, 1.0f);
	/*wrap.UnsetTarget();
	wrap.BlitRect(ct, 0,0,100,100);*/
	//OutputDebugStringA("test");
	return true;
}

//int main()
//[](GfxWrap &wrap) {wrap.Clear(GfxColor(90, 0, 20, 0)); return true; }
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	GfxWrap gfx;
	gfx.Init("test", 800, 600, GfxMain);
	lt = gfx.LoadTexture("c:/Media/metal_1024.png");
	ct = gfx.CreateTexture(256, 256);

	gfx.Begin();

}
