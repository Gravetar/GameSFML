#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

void PlayerGoordForView(float x, float y)
{
	view.setCenter(x + 100, y);
}