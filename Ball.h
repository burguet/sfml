#pragma once
#include "Player.h"
#include "brick.h"
#include <SFML/Graphics.hpp>

class Ball
{
private:
	sf::CircleShape shape;
	sf::Vector2f oldPosition;
	sf::Vector2f position;

	float speed;
	int radius;
	sf::Vector2f direction;
	static bool isRandInitialized;
	double randomizeAngle();
	void setAngle(double angle);


public:
	Ball(int x, int y, int radius, float speed);
	~Ball();
	void move(float ellapsedTime);
	void draw(sf::RenderWindow& window);

	float getSpeed() const;
	void setSpeed(float newSpeed);

	void setPosition(sf::Vector2f newPosition);
	void setDirection(sf::Vector2f newDirection);

	sf::Vector2f getPosition() const;
	sf::CircleShape& getShape();

	void manageCollisionWith(Player& player, sf::RenderWindow& window);
	bool checkCollisionWith(Player& player);
	void manageCollisionWithBrick(Brick& brick);

};