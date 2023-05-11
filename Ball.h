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
	float getSpeed();
	void setSpeed(float newSpeed);
	void setPosition(sf::Vector2f newPosition);
	sf::Vector2f getPosition();
	void setDirection(sf::Vector2f newDirection);

	void manageCollisionWith(Player& player, sf::RenderWindow& window);
	void manageCollisionWith(Brick& brick);
	sf::CircleShape& getShape();
	bool checkCollisionWith(Player& player) ;
	bool checkCollisionWith(Brick& brick);
};

