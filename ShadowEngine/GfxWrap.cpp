#include "pch.h"


GfxWrap::GfxWrap() {
}


GfxWrap::~GfxWrap() {
}


GfxKey GfxWrap::NextTextureKey() {
	return _nextTextureKey++;
}


//bool(*mainCallback)(GfxWrap&)
bool GfxWrap::Init(std::string title, int windowWidth, int windowHeight, std::function<bool(GfxWrap&)> mainCallback=nullptr) {
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

bool GfxWrap::DrawTexture(GfxKey key) {
	auto iter = _textures.find(key);
	if (iter != _textures.end()) {
		if (_targetTexture == nullptr) {
			//_window.draw( *(iter->second->_getSprite()) );
			sf::RenderTexture* tex = iter->second->_getTexture();
			sf::Sprite* sprite = iter->second->_getSprite();

			tex->display();
			sprite->setTexture(tex->getTexture());
			sprite->setPosition(100, 100);
			sprite->setTextureRect({ 0,0,100,100 });
			_window.draw(*sprite);
		}
		else {
			/*sf::RenderTexture* tex = _targetTexture->_getTexture();
			sf::Sprite* sprite = _targetTexture->_getSprite();

			tex->display();
			sprite->setTexture(tex->getTexture());
			sprite->setPosition(100,100);
			_targetTexture->get*/
		}
	}

	return false;
}

void GfxWrap::SetTarget(GfxTexture* newTarget) {
	_targetTexture = newTarget;
}


void GfxWrap::UnsetTarget() {
	_targetTexture = nullptr;
}


GfxKey GfxWrap::LoadTexture(std::string filename) {
	auto newTex = std::make_shared<GfxTexture>();
	bool loadRet = newTex->Load(filename);
	GfxKey newKey = GfxWrap::Invalid;

	if (loadRet) {
		newKey = NextTextureKey();
		_textures.insert(std::make_pair(newKey, newTex));
	}

	return newKey;
}

GfxKey GfxWrap::CreateTexture(int width, int height) {
	auto newTex = std::make_shared<GfxTexture>();
	bool createRet = newTex->Create(width, height);
	GfxKey newKey = GfxWrap::Invalid;

	if (createRet) {
		newKey = NextTextureKey();
		_textures.insert( std::make_pair(newKey, newTex) );
	}

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