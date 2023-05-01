#include <SFML/Graphics.hpp>
#include "Ball.h"

double mapValue(double value, double min, double max, double nMin, double nMax)
{
	// Y = (X-A)/(B-A) * (D-C) + C
	double newVal = (((value - min) / (max - min)) * (nMax - nMin)) + nMin;
	return newVal;
}

int main(int argc, char **argv)
{
	Ball ball(200, 250, 10, 4000);
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	

	sf::RectangleShape bar(sf::Vector2f(200.f, 20.f));
	bar.setFillColor(sf::Color::Green);
	bar.setPosition(300.f, 550.f);

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(100, 50));
	rectangle.setFillColor(sf::Color::Cyan);
	rectangle.setOutlineColor(sf::Color::Magenta);
	rectangle.setOutlineThickness(2);
	rectangle.setPosition(200, 200);


	sf::RectangleShape rectangle2;
	rectangle2.setSize(sf::Vector2f(100, 50));
	rectangle2.setFillColor(sf::Color::Cyan);
	rectangle2.setOutlineColor(sf::Color::Magenta);
	rectangle2.setOutlineThickness(2);
	rectangle2.setPosition(305, 200);

	sf::RectangleShape rectangle3;
	rectangle3.setSize(sf::Vector2f(100, 50));
	rectangle3.setFillColor(sf::Color::Cyan);
	rectangle3.setOutlineColor(sf::Color::Magenta);
	rectangle3.setOutlineThickness(2);
	rectangle3.setPosition(410, 200);

	sf::RectangleShape rectangle4;
	rectangle4.setSize(sf::Vector2f(100, 50));
	rectangle4.setFillColor(sf::Color::Cyan);
	rectangle4.setOutlineColor(sf::Color::Magenta);
	rectangle4.setOutlineThickness(2);
	rectangle4.setPosition(200, 255);

	sf::RectangleShape rectangle5;
	rectangle5.setSize(sf::Vector2f(100, 50));
	rectangle5.setFillColor(sf::Color::Cyan);
	rectangle5.setOutlineColor(sf::Color::Magenta);
	rectangle5.setOutlineThickness(2);
	rectangle5.setPosition(305, 255);

	sf::RectangleShape rectangle6;
	rectangle6.setSize(sf::Vector2f(100, 50));
	rectangle6.setFillColor(sf::Color::Cyan);
	rectangle6.setOutlineColor(sf::Color::Magenta);
	rectangle6.setOutlineThickness(2);
	rectangle6.setPosition(410, 255);

	sf::RectangleShape rectangle7;
	rectangle7.setSize(sf::Vector2f(100, 50));
	rectangle7.setFillColor(sf::Color::Cyan);
	rectangle7.setOutlineColor(sf::Color::Magenta);
	rectangle7.setOutlineThickness(2);
	rectangle7.setPosition(200, 310);

	sf::RectangleShape rectangle8;
	rectangle8.setSize(sf::Vector2f(100, 50));
	rectangle8.setFillColor(sf::Color::Cyan);
	rectangle8.setOutlineColor(sf::Color::Magenta);
	rectangle8.setOutlineThickness(2);
	rectangle8.setPosition(305, 310);

	sf::RectangleShape rectangle9;
	rectangle9.setSize(sf::Vector2f(100, 50));
	rectangle9.setFillColor(sf::Color::Cyan);
	rectangle9.setOutlineColor(sf::Color::Magenta);
	rectangle9.setOutlineThickness(2);
	rectangle9.setPosition(410, 310);
	




	sf::RectangleShape rdr2;
	rdr2.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	
	sf::Clock clock;
	sf::Vector3f xFactor(10, 20, 30);
	float ellapsedTime = 0;

	// on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen())
	{
		ellapsedTime = clock.restart().asSeconds();
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window.pollEvent(event))
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();


		}

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		float x = static_cast<float>(mousePosition.x);
		float barPositionX = x - bar.getSize().x / 2.f;
		bar.setPosition(barPositionX, bar.getPosition().y);

		if (ball.getPosition().y + ball.getRadius() > bar.getPosition().y &&
			ball.getPosition().x + ball.getRadius() > bar.getPosition().x &&
			ball.getPosition().x - ball.getRadius() < bar.getPosition().x + bar.getSize().x)
		{
			ballVelocity.y = -ballVelocity.y;
		}

		// Rebondir sur les bords de la fenêtre
		if (ball.getPosition().x - ball.getRadius() < 0 || ball.getPosition().x + ball.getRadius() > window.getSize().x)
		{
			ballVelocity.x = -ballVelocity.x;
		}

		if (ball.getPosition().y - ball.getRadius() < 0 || ball.getPosition().y + ball.getRadius() > window.getSize().y)
		{
			ballVelocity.y = -ballVelocity.y;
		}

		ball.move(ellapsedTime);
		ball.manageCollisionWith(window);

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

		window.draw(rectangle);
		window.draw(rectangle2);
		window.draw(rectangle3);
		window.draw(rectangle4);
		window.draw(rectangle5);
		window.draw(rectangle6);
		window.draw(rectangle7);
		window.draw(rectangle8);
		window.draw(rectangle9);
		window.draw(bar);

		ball.draw(window);
		window.display();
	}

	return 0;
}