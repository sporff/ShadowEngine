#include "pch.h"


GfxWrap::GfxWrap() {
}


GfxWrap::~GfxWrap() {
}
//bool(*mainCallback)(GfxWrap&)
bool GfxWrap::Init(std::string title, int windowWidth, int windowHeight, std::function<bool(GfxWrap&)> mainCallback) {
	try {
		_window.create(sf::VideoMode(windowWidth, windowHeight), title.c_str());
	}
	catch (std::exception e) {
		std::cout << e.what();
	}

	_mainCallback = mainCallback;

	return false;
}

void GfxWrap::Shutdown() {
	_window.close();
}

void GfxWrap::Clear() {
	_window.clear();
}

void GfxWrap::Clear( GfxColor clr ) {
	_window.clear(clr);
}

bool GfxWrap::Present() {
	_window.display();
	return true;
}


void GfxWrap::SetTarget(GfxTexture* newTarget) {
	_targetTexture = newTarget;
}


void GfxWrap::UnsetTarget() {
	_targetTexture = nullptr;
}


bool GfxWrap::LoadTexture(std::string filename) {
	return false;
}

bool GfxWrap::CreateTexture(int width, int height) {
	GfxTexture newTex;
	newTex.Create(width, height);

	return false;
}


void GfxWrap::Begin() {
	bool done = false;
	while (_window.isOpen())
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::KeyPressed:
				OutputDebugStringA("Key pressed\n");
				break;
			case sf::Event::KeyReleased:
				OutputDebugStringA("Key released\n");
				break;
			}
			 
			if (event.type == sf::Event::Closed)
				Shutdown();

			sf::Vector2i mouse = sf::Mouse::getPosition(_window);

			//Clear(GfxColor(50,20,50,0));
		}
	
		if (_mainCallback != nullptr) {
			if (!_mainCallback(*this))
				done = true;
		}

		Present();
	}
}