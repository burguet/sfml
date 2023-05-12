#include "Ball.h"

bool Ball::isRandInitialized = false;

Ball::Ball(int x, int y, int radius, float speed) :
	position(x, y),
	oldPosition(position),
	direction(1.f, 1.f),
	radius(radius),
	speed(speed)
	
{
	shape.setFillColor(sf::Color::White);
	shape.setRadius(radius);
	setAngle(randomizeAngle());
}

Ball::~Ball()
{
} 

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



void Ball::move(float elapsedTime)
{
	oldPosition = position;
	position += elapsedTime * speed * direction;
	shape.setPosition(position);
}

void Ball::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

float Ball::getSpeed() const
{
	return speed;
}


void Ball::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	oldPosition = position;
	shape.setPosition(position);
}

sf::Vector2f Ball::getPosition() const
{
	return position;
}

void Ball::setDirection(sf::Vector2f newDirection)
{
	direction = newDirection;
}

void Ball::manageCollisionWith( Player& player, sf::RenderWindow& window)
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

void Ball::manageCollisionWithBrick(Brick& brick)
{
	// Créer le rectangle de la zone de collision de la balle avec la barre
	sf::FloatRect ballRect(position.x, position.y, 2 * radius, 2 * radius);
	sf::FloatRect briqueRect(brick.getPosition().x, brick.getPosition().y, brick.getSize().x, brick.getSize().y);

	// Vérifier si la zone de collision de la balle intersecte le rectangle de la barre
	if (ballRect.intersects(briqueRect)) {

		// Calcule la position relative de la balle par rapport à la brique
		double relativeIntersectX = position.x + radius - brick.getPosition().x - brick.getSize().x / 2.0;
		double relativeIntersectY = position.y + radius - brick.getPosition().y - brick.getSize().y / 2.0;

		// Normalise la position relative de la balle
		double normalizedRelativeIntersectionX = relativeIntersectX / (brick.getSize().x / 2.0);
		double normalizedRelativeIntersectionY = relativeIntersectY / (brick.getSize().y / 2.0);

		// Déterminer quelle surface de la brique a été touchée
		if (std::abs(normalizedRelativeIntersectionX) > std::abs(normalizedRelativeIntersectionY)) {
			// La balle a touché le côté gauche ou droit de la brique
			if (normalizedRelativeIntersectionX > 0) {
				// La balle a touché le côté droit de la brique
				position.x = brick.getPosition().x + brick.getSize().x + radius;
				brick.hit();
			}
			else {
				// La balle a touché le côté gauche de la brique
				position.x = brick.getPosition().x - 2 * radius;
				brick.hit();
			}
			direction.x = -direction.x;
		}
		else {
			// La balle a touché le haut ou le bas de la brique
			if (normalizedRelativeIntersectionY > 0) {
				// La balle a touché le bas de la brique
				position.y = brick.getPosition().y + brick.getSize().y + radius;
				brick.hit();
			}
			else {
				// La balle a touché le haut de la brique
				position.y = brick.getPosition().y - 2 * radius;
				brick.hit();
			}
			direction.y = -direction.y;
		}
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

