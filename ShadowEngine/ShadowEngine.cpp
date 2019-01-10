// ShadowEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

//int main()
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML window");

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			sf::Vector2i mouse = sf::Mouse::getPosition(window);
			window.clear(sf::Color(50, 20, 50, 0));
			window.display();
		}
	}
}