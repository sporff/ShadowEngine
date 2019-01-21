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
	//_window.clear();


	if (_targetTexture != nullptr) {
		_targetTexture->_getTexture()->clear();
	}
	else {
		_window.clear();
	}
}

void GfxWrap::Clear( GfxColor clr ) {
	_window.clear(clr);
}

bool GfxWrap::Present() {
	_window.display();
	return true;
}


bool GfxWrap::SetTarget(GfxKey key) {
	_targetTexture = _getTexture(key);
	if (_targetTexture == nullptr) {
		return false;
	}

	return true;
}


void GfxWrap::UnsetTarget() {
	_targetTexture = nullptr;
}


bool GfxWrap::Blit(GfxKey key, double x, double y, double width, double height) {
	auto getTex = _getTexture(key);

	if (getTex == nullptr) {
		Logger::dprint({ "Error finding texture: ", std::to_string(key) });
		return false;
	}

	sf::RectangleShape rs;
	sf::RenderTexture *rt = getTex->_getTexture();
	if (rt == nullptr) {
		Logger::dprint({ "Error finding texture: ", std::to_string(key) });
		return false;
	}

	//rs.setFillColor(sf::Color(150, 50, 50));
	rs.setTexture(&rt->getTexture());
	rs.setPosition(sf::Vector2f((float)x, (float)y));
	rs.setSize(sf::Vector2f( (float)width, (float)height));
	//rs.setOrigin(width*0.5f, height*0.5f);

	if (_targetTexture != nullptr) {
		_targetTexture->_getTexture()->draw(rs);
	}
	else {
		_window.draw(rs);
	}

	return true;
}

bool GfxWrap::BlitEx(GfxKey key, double x, double y, double width, double height, double ox, double oy, double degrees, double scale) {
	auto getTex = _getTexture(key);

	if (getTex == nullptr) {
		Logger::dprint({ "Error finding texture: ", std::to_string(key) });
		return false;
	}

	sf::RectangleShape rs;
	sf::RenderTexture *rt = getTex->_getTexture();
	if (rt == nullptr) {
		Logger::dprint({ "Error finding texture: ", std::to_string(key) });
		return false;
	}

	//rs.setFillColor(sf::Color(150, 50, 50));
	rs.setTexture(&rt->getTexture());
	rs.setPosition(sf::Vector2f((float)x, (float)y));
	rs.setSize(sf::Vector2f((float)width, (float)height));
	rs.setOrigin(ox, oy);
	rs.setRotation(degrees);
	rs.setScale(scale, scale);

	if (_targetTexture != nullptr) {
		_targetTexture->_getTexture()->draw(rs);
	}
	else {
		_window.draw(rs);
	}

	return true;
}

// Load a texture and store it in the map
GfxKey GfxWrap::LoadTexture(std::string filename) {
	auto newTex = std::make_shared<GfxTexture>();

	bool loadRet = newTex->Load(filename);
	if (loadRet == false) {
		return InvalidKey;
	}

	GfxKey insertedKey = _getNextTextureKey();
	_textures.insert(std::make_pair(insertedKey, newTex));

	return insertedKey;
}

// Create a texture and store it in the map
GfxKey GfxWrap::CreateTexture(int width, int height) {
	auto newTex = std::make_shared<GfxTexture>();
	
	if (!newTex->Create(width, height)) {
		return InvalidKey;
	}

	GfxKey insertedKey = _getNextTextureKey();
	_textures.insert( std::make_pair(insertedKey, newTex) );

	return insertedKey;
}

// Get next texture key and increment to the next index
GfxKey GfxWrap::_getNextTextureKey() {
	return _nextTextureKey++;
}

std::shared_ptr<GfxTexture> GfxWrap::_getTexture(GfxKey key) {
	auto foundTex = _textures.find(key);
	if (foundTex == _textures.end()) {
		Logger::dprint({"Error finding texture: ", std::to_string(key)});
		return nullptr;
	}

	return foundTex->second;
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