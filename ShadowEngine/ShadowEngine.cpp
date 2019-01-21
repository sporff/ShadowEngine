// ShadowEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

GfxKey lt = 0;
GfxKey ct = 0;

static bool GfxMain(GfxWrap &wrap) {
	wrap.Clear(GfxColor(20,90,20,0));

	//wrap.SetTarget(ct);
	wrap.BlitEx(lt, 100,100,200,200, 100, 100, 45, 1.0f);
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
