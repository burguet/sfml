#include <SFML/Graphics.hpp>
#include "Player.h"


Player::Player(int y, int width, int height)
{
	this->y = y;
	this->size.x = width;
	this->size.y = height;

	shape.setSize(this->size);
	shape.setFillColor(sf::Color::White);
	shape.setPosition(sf::Vector2f(400 - (size.x / 2), y));
}

Player::~Player()
{
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

sf::Vector2f Player::getPosition()
{
	return this->shape.getPosition();
}

sf::Vector2f Player::getSize()
{
	return this->size;
}

void Player::move(const sf::Vector2f& mousePosition, float deltaTime)
{
	// Calculer la nouvelle position du joueur en fonction de la position de la souris
	position.x = mousePosition.x - size.x / 2.f;
	position.y = y;

	// Vérifier si la barre sort de l'écran
	if (position.x < 0) {
		position.x = 0;
	}
	else if (position.x + size.x > 800) { // 800 est la largeur de l'écran
		position.x = 800 - size.x;
	}

	// Déplacer le joueur
	shape.setPosition(position);
}

sf::RectangleShape& Player::getShape()
{
	return shape;
}