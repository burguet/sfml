#include "Ball.h"

bool Ball::isRandInitialized = false;

double Ball::randomizeAngle()
{
	if (!isRandInitialized)
	{
		srand(time(NULL));
		isRandInitialized = true;
	}

	return (((double)rand() / (double)RAND_MAX) * 60.0) - 30.0;
}

void Ball::setAngle(double angle)
{
	direction.x = sin(angle);
	direction.y = -cos(angle);
}

Ball::Ball(int x, int y, int radius, float speed)
{
	position.x = x;
	position.y = y;
	oldPosition = position;
	shape.setFillColor(sf::Color(sf::Color::White));
	this->radius = radius;
	shape.setRadius(radius);
	this->speed = speed;

	setAngle(randomizeAngle());
}

Ball::~Ball()
{
}

void Ball::move(float ellapsedTime)
{
	position += ellapsedTime * speed * direction;
}

void Ball::draw(sf::RenderWindow & window)
{
	shape.setPosition(position);
	window.draw(shape);
}

float Ball::getSpeed()
{
	return speed;
}

void Ball::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Ball::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	oldPosition = position;
}

sf::Vector2f Ball::getPosition()
{
	return position;
}

void Ball::setDirection(sf::Vector2f newDirection)
{
	direction = newDirection;
}

void Ball::manageCollisionWith(Player& player, sf::RenderWindow& window)
{
	// Si la balle sort de l'écran (par en haut)
	if (position.y <= 0)
	{
		// Inverse la direction sur l'axe y :
		direction.y *= -1;
		position.y = 0;
	}
	else if (position.y + 2 * radius >= window.getSize().y)
	{
		direction.y *= -1;
		position.y = window.getSize().y - 2 * radius;
	}

	if (position.x <= 0)
	{
		direction.x *= -1;
		position.x = 0;
	}
	else if (position.x + 2 * radius >= window.getSize().x)
	{
		direction.x *= -1;
		position.x = window.getSize().x - 2 * radius;
	}

	// Vérifiez si la balle touche le joueur
	if (shape.getGlobalBounds().intersects(player.getShape().getGlobalBounds()))
	{
		// Calcule la position relative de la balle par rapport au joueur
		float relativePosition = (position.x + radius) - (player.getPosition().x + player.getSize().x / 2);

		// Modifie la direction de la balle en fonction de la position relative
		direction.x = relativePosition / (player.getSize().x / 2);
		direction.y *= -1;

		// Placez la balle au-dessus du joueur pour éviter qu'elle reste collée
		position.y = player.getPosition().y - radius * 2;
	}


}

sf::CircleShape& Ball::getShape()
{
	return shape;
}

bool Ball::checkCollisionWith( Player& player) 
{
	return shape.getGlobalBounds().intersects(player.getShape().getGlobalBounds());
}

