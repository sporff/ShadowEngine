// ShadowEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

GfxKey key;

static bool GfxMain(GfxWrap &wrap) {
	int x = 0;
	wrap.Clear(GfxColor(20,90,20,0));
	wrap.DrawTexture(key);

	
	//OutputDebugStringA( (std::to_string(x++) + std::string("\n")).c_str() );
	return true;
}


//[](GfxWrap &wrap) {wrap.Clear(GfxColor(90, 0, 20, 0)); return true; }
//int main()
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	GfxWrap gfx;
	gfx.Init("test test", 800, 600, GfxMain);
	key = gfx.LoadTexture("c:/Media/metal_1024.jpg");

	gfx.Begin();
}

