#include "pch.h"


GfxWrap::GfxWrap() {
}


GfxWrap::~GfxWrap() {
}
//bool(*mainCallback)(GfxWrap&)
bool GfxWrap::Init(std::string title, int windowWidth, int windowHeight, std::function<bool(GfxWrap&)> mainCallback) {
	sf::ContextSettings cs;
	sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close;

	try {
		_window.create(sf::VideoMode(windowWidth, windowHeight), title.c_str(), style);
	}
	catch (std::exception e) {
		std::cout << e.what();
	}

	_mainCallback = mainCallback;
	UnsetTarget();

	return false;
}

void GfxWrap::Shutdown() {
	_window.close();
}

GfxVector2i GfxWrap::GetMousePos() {
	return sf::Mouse::getPosition(_window);
}

void GfxWrap::Clear() {
	_renderTarget->clear();
	
}

void GfxWrap::Clear( GfxColor clr ) {
	_renderTarget->clear(clr);
}

void GfxWrap::Present() {
	if (_targetIsWindow == true)
		_window.display();
	else if (_renderTarget != nullptr)
		static_cast<sf::RenderTexture*>(_renderTarget)->display();
}


bool GfxWrap::SetTarget(GfxKey key) {
	auto gotTexture = _getTexture(key);

	if (gotTexture == nullptr) {
		_renderTarget = &_window;
		return false;
	}

	_renderTarget = gotTexture->_getTexture();
	_targetIsWindow = false;
	return true;
}


void GfxWrap::UnsetTarget() {
	_targetIsWindow = true;
	_renderTarget = &_window;
}


bool GfxWrap::Blit(GfxKey key, float x, float y, float width, float height) {
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

	rs.setTexture(&rt->getTexture());
	rs.setPosition(sf::Vector2f((float)x, (float)y));
	rs.setSize(sf::Vector2f( (float)width, (float)height));
	rs.setOrigin(0.0f, 0.0f);

	_renderTarget->draw(rs, sf::BlendNone);

	return true;
}

bool GfxWrap::BlitEx(GfxKey key, float x, float y, float width, float height, float ox, float oy, float degrees, float scale, GfxBlendMode blendMode=GfxBlendNone) {
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

	sf::BlendMode sfBlendMode;
	switch (blendMode) {
	case GfxBlendAdd:
		sfBlendMode = sf::BlendAdd;
		break;
	case GfxBlendMod:
		sfBlendMode = sf::BlendMultiply;
		break;
	case GfxBlendAlpha:
		sfBlendMode = sf::BlendAlpha;
		break;
	case GfxBlendNone:
	default:
		sfBlendMode = sf::BlendNone;
		break;
	}
	_renderTarget->draw(rs, sfBlendMode);

	return true;
}

bool GfxWrap::BlitEx(GfxKey key, float x, float y, float width, float height, float ox, float oy, float degrees, float scale, float texScale, GfxBlendMode blendMode)
{
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
	rt->setRepeated(true);
	rs.setTexture(&rt->getTexture());
	auto texSize = rs.getSize();
	//sf::IntRect texRect(0, 0, (int)(texScale * (float)texSize.x), (int)(texScale*(float)texSize.y));
	sf::IntRect texRect(0, 0, 2048.f, 2048.f);
	rs.setTextureRect(texRect);
	rs.setPosition(sf::Vector2f((float)x, (float)y));
	rs.setSize(sf::Vector2f((float)width, (float)height));
	rs.setOrigin(ox, oy);
	rs.setRotation(degrees);
	rs.setScale(scale, scale);

	sf::BlendMode sfBlendMode;
	switch (blendMode) {
	case GfxBlendAdd:
		sfBlendMode = sf::BlendAdd;
		break;
	case GfxBlendMod:
		sfBlendMode = sf::BlendMultiply;
		break;
	case GfxBlendAlpha:
		sfBlendMode = sf::BlendAlpha;
		break;
	case GfxBlendNone:
	default:
		sfBlendMode = sf::BlendNone;
		break;
	}
	_renderTarget->draw(rs, sfBlendMode);

	return true;
}


void GfxWrap::DrawLine(float x1, float y1, float x2, float y2, GfxColor clr) {
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(x1, y1), clr),
		sf::Vertex(sf::Vector2f(x2, y2), clr)
	};
	_renderTarget->draw(line, 2, sf::Lines);

	//sf::VertexArray line(sf::Lines, 2);
	//line[0].position = { (float)x1, (float)y1 };
	//line[1].position = { (float)x1, (float)y1 };

	//line[0].color = clr;
	//line[1].color = clr;

	//_renderTarget->draw(line);

}


void GfxWrap::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, GfxColor clr) {
	sf::VertexArray triangle(sf::Triangles, 3);

	triangle[0].position = { (float)x1, (float)y1 };
	triangle[1].position = { (float)x2, (float)y2 };
	triangle[2].position = { (float)x3, (float)y3 };

	triangle[0].color = clr;
	triangle[1].color = clr;
	triangle[2].color = clr;

	_renderTarget->draw(triangle);
}

void GfxWrap::DrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, GfxColor clr) {
	sf::VertexArray quad(sf::Quads, 4);

	quad[0].position = { (float)x1, (float)y1 };
	quad[1].position = { (float)x2, (float)y2 };
	quad[2].position = { (float)x3, (float)y3 };
	quad[3].position = { (float)x4, (float)y4 };

	quad[0].color = clr;
	quad[1].color = clr;
	quad[2].color = clr;
	quad[3].color = clr;

	_renderTarget->draw(quad);
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