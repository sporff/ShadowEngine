// ShadowEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"


static bool GfxMain(GfxWrap &wrap) {
	wrap.Clear(GfxColor(20,90,20,0));
	//OutputDebugStringA("test");
	return true;
}

//int main()
//[](GfxWrap &wrap) {wrap.Clear(GfxColor(90, 0, 20, 0)); return true; }
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	GfxWrap gfx;
	gfx.Init("test", 800, 600, GfxMain);

	gfx.Begin();

	auto f = []() {};
}

