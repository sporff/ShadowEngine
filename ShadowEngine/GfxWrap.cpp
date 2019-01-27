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
	_renderTarget = &_window;

	return false;
}

void GfxWrap::Shutdown() {
	_window.close();
}

void GfxWrap::Clear() {
	_renderTarget->clear();
	
}

void GfxWrap::Clear( GfxColor clr ) {
	_renderTarget->clear(clr);
}

bool GfxWrap::Present() {
	_window.display();
	return true;
}


bool GfxWrap::SetTarget(GfxKey key) {
	_renderTarget = _getTexture(key)->_getTexture();
	if (_renderTarget == nullptr) {
		_renderTarget = &_window;
		return false;
	}

	return true;
}


void GfxWrap::UnsetTarget() {
	_renderTarget = &_window;
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

	_renderTarget->draw(rs);

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

	_renderTarget->draw(rs);

	return true;
}

//void GfxWrap::DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, GfxColor clr) {
//	//sf::RenderTarget
//	if (_targetTexture != nullptr) {
//		_targetTexture->DrawTriangle(x1, y1, x2, y2, x3, y3, clr);
//	}
//	else {
//		//sf::RenderTarget *w = &_window;
//		//_window.draw(rs);
//	}
//}

void GfxWrap::DrawLine(double x1, double y1, double x2, double y2, GfxColor clr) {
	/*sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(x1, y1), clr),
		sf::Vertex(sf::Vector2f(x2, y2), clr)
	};
	_texture.draw(line, 2, sf::Lines);*/

	//if ()

	sf::VertexArray line(sf::Lines, 2);
	line[0].position = { (float)x1, (float)y1 };
	line[1].position = { (float)x1, (float)y1 };

	line[0].color = clr;
	line[1].color = clr;

	_renderTarget->draw(line);

}


void GfxWrap::DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, GfxColor clr) {
	sf::VertexArray triangle(sf::Triangles, 3);

	triangle[0].position = { (float)x1, (float)y1 };
	triangle[1].position = { (float)x2, (float)y2 };
	triangle[2].position = { (float)x3, (float)y3 };

	triangle[0].color = clr;
	triangle[1].color = clr;
	triangle[2].color = clr;

	_renderTarget->draw(triangle);
}

void GfxWrap::DrawQuad(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, GfxColor clr) {

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