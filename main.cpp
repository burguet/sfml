#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "brick.h"
#include "Player.h"

double mapValue(double value, double min, double max, double nMin, double nMax)
{
	// Y = (X-A)/(B-A) * (D-C) + C
	double newVal = (((value - min) / (max - min)) * (nMax - nMin)) + nMin;
	return newVal;
}

int main(int argc, char **argv)
{

	Ball ball(200, 250, 10, 500);
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	


	std::vector<Brick> bricks;

	const int brickWidth = 100;
	const int brickHeight = 50;
	const int numRows = 3;
	const int numCols = 10;

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			int x = j * (brickWidth + 10) + 50;
			int y = i * (brickHeight + 10) + 50;

			// v�rifier si la brique est dans l'�cran
			if (x + brickWidth <= window.getSize().x && y + brickHeight <= window.getSize().y) {
				Brick brick(x, y, brickWidth, brickHeight, 3 - i);
				bricks.push_back(brick);
			}
		}
	}

	Player player(550, 100, 10);

	sf::RectangleShape rdr2;
	rdr2.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	
	sf::Clock clock;
	sf::Vector3f xFactor(10, 20, 30);
	float ellapsedTime = 0;

	// on fait tourner le programme jusqu'� ce que la fen�tre soit ferm�e
	while (window.isOpen())
	{
		float deltaTime = clock.getElapsedTime().asSeconds();
		ellapsedTime = clock.restart().asSeconds();
		// on inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
		sf::Event event;
		while (window.pollEvent(event))
		{
			// �v�nement "fermeture demand�e" : on ferme la fen�tre
			if (event.type == sf::Event::Closed)
				window.close();
			

		}

		
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
		player.move(mousePosition, deltaTime);

		ball.move(ellapsedTime);
		
		ball.manageCollisionWith(player, window);

		window.clear();


		//for (int i = 0; i < window.getSize().y; i++)
		//{
			double mappedValue = mapValue(ball.getPosition().x, 0, window.getSize().x, 0, 255);
			double mappedValue2 = mapValue(ball.getPosition().y, 0, window.getSize().y, 0, 255);
			double mappedValue3 = (mappedValue + mappedValue2) / 2.0;
			rdr2.setFillColor(sf::Color(mappedValue, 255 - mappedValue2, mappedValue3));
			
		//}

		rdr2.setPosition(0, 0);
		window.draw(rdr2);
		ball.draw(window);
		for (Brick& brick : bricks)
		{
			if (brick.isAlive())
			{
				brick.draw(window);
			}
		}
		player.draw(window);
		window.display();
	}
	

	return 0;
}