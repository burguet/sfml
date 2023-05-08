#include "brick.h"

Brick::Brick(int x, int y, int width, int height, int health) :
	position(sf::Vector2f(x, y)),
	size(sf::Vector2f(width, height)),
	health(health)
{
	shape.setSize(size);
	shape.setFillColor(getColorFromLife());
	shape.setPosition(position);
}

Brick::~Brick()
{

}

void Brick::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

sf::Color Brick::getColorFromLife()
{
	if (health >= 4) {
		return sf::Color::Red;
	}
	else if (health >= 2) {
		return sf::Color::Yellow;
	}
	else {
		return sf::Color::Green;
	}
}

bool Brick::isAlive()
{
	return health > 0;
}

void Brick::hit()
{
	health--;
	shape.setFillColor(getColorFromLife());
}

sf::Vector2f Brick::getPosition()
{
	return position;
}

sf::Vector2f Brick::getSize()
{
	return size;
}