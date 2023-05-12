#include "brick.h"

Brick::Brick(int x, int y, int width, int height, int health) 
	
{
	this->position = sf::Vector2f(x, y);
	this->size = sf::Vector2f(width, height);
	this->shape = sf::RectangleShape(size);
	this->health = health;
	shape.setFillColor(sf::Color::Green); // Couleur initiale est vert
	this->shape.setOutlineColor(sf::Color::White); // Blanc
	this->shape.setOutlineThickness(1); // Largeur de 1 pixel pour le contour
	this->lastCollisionTime = 0; // Initialisation du temps de la derni�re collision � z�ro
}

Brick::~Brick()
{

}

void Brick::draw(sf::RenderWindow& window)
{

	if (isAlive())
	{
		// Si la brique est encore en vie, dessiner la forme sur la fen�tre donn�e
		shape.setPosition(position);
		window.draw(shape);
	}
}



bool Brick::isAlive()
{
	return health > 0;
}

void Brick::hit()
{
	if (isAlive())
	{
		// Si la brique est encore en vie et si le temps depuis la derni�re collision est sup�rieur ou �gal � une seconde,
		// r�duire sa sant�, changer sa couleur et mettre � jour le temps de la derni�re collision
		if (clock.getElapsedTime().asSeconds() - lastCollisionTime >= 0.1) {
			health--;
			setColor();
			lastCollisionTime = clock.getElapsedTime().asSeconds();
		}
	}
}

sf::Vector2f Brick::getPosition()
{
	return position;
}

sf::Vector2f Brick::getSize()
{
	return size;
}

sf::RectangleShape Brick::getShape()
{
	// Renvoyer la forme de la brique
	return shape;
}

void Brick::setColor()
{
	this->shape.setOutlineColor(sf::Color::White); // Blanc
	this->shape.setOutlineThickness(1); // Largeur de 1 pixel pour le contour
	if (this->health == 2)
	{
		// Si la sant� est de 2, changer la couleur � orange
		this->shape.setFillColor(sf::Color(255, 165, 0)); // Orange
	}
	else if (this->health == 1)
	{
		// Si la sant� est de 1, changer la couleur � rouge
		this->shape.setFillColor(sf::Color::Red); // Rouge
	}
}

bool Brick::operator==(const Brick& other) const
{
	// Renvoyer true si cette brique est la m�me que l'autre brique, sinon false
	return this == &other;
}

void Brick::destroyAndDelete(std::deque<Brick*>& bricks)
{
	// Retirer la brique de la deque de briques
	bricks.erase(std::remove(bricks.begin(), bricks.end(), this), bricks.end());
	// Supprimer l'objet de la m�moire
	delete this;
}