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

	// Déplacer le joueur
	shape.setPosition(position);
}