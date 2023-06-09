#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::RectangleShape shape;
	sf::Vector2f position;
	sf::Vector2f size;
	int y;
public:
	Player(int y, int width, int height);
	~Player();
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	void move(const sf::Vector2f& mousePosition, float deltaTime);
	sf::RectangleShape& getShape();
};
