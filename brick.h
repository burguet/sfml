#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
	class Brick
	{
	private:
		sf::RectangleShape shape;
		sf::Vector2f position;
		sf::Vector2f size;
		int health;
		sf::Clock clock;
		float lastCollisionTime;
		void setColor();

	public:
		sf::Vector2f getPosition();
		sf::Vector2f getSize();
		sf::RectangleShape getShape();

		Brick(int x, int y, int width, int height, int health);
		~Brick();

		void draw(sf::RenderWindow& window);
		bool isAlive();
		void hit();
		bool operator==(const Brick& other) const;
		void destroyAndDelete(std::deque<Brick*>& bricks);
	};


