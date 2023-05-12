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

	
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	

	// Création de la plateforme, de la balle, des bricks et de la fenêtre
	std::deque<Brick*> bricks;
	Player player(550, 100, 11);
	Ball ball(200, 250, 10, 550); // x,y,size,speedddd



	


	int numBricksPerLine = 10; // Nombre de briques par ligne
	int brickWidth = 80; // Largeur d'une brique
	int brickHeight = 30; // Hauteur d'une brique
	int horizontalSpacing = (800 - numBricksPerLine * brickWidth) / (numBricksPerLine + 1); // Espacement horizontal entre les briques
	int verticalSpacing = 30; // Espacement vertical entre les briques
	for (int i = 0; i < 4; i++) { // Boucle pour créer 4 lignes de bricks
		for (int j = 0; j < numBricksPerLine; j++) { // Boucle pour créer le nombre de briques spécifié par ligne
			int x = horizontalSpacing + j * (brickWidth + horizontalSpacing); // Position x de la brick en fonction de j
			int y = verticalSpacing + i * (brickHeight + verticalSpacing); // Position y de la brick en fonction de i
			bricks.push_back(new Brick(x, y, brickWidth, brickHeight, 3)); // Création d'une nouvelle brick et ajout dans la deque
		}
	}

	

	
	const int numRows = 3;
	const int numCols = 10;

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			int x = j * (brickWidth + 10) + 50;
			int y = i * (brickHeight + 10) + 50;

			// vérifier si la brique est dans l'écran
			if (x + brickWidth <= window.getSize().x && y + brickHeight <= window.getSize().y) {
				Brick * brick = new Brick(x, y, brickWidth, brickHeight, 3 - i);
				bricks.push_back(brick);
			}
		}
	}

	
	

	sf::RectangleShape rdr2;
	rdr2.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	
	sf::Clock clock;
	sf::Vector3f xFactor(10, 20, 30);
	float ellapsedTime = 0;

	// on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen())
	{
		float deltaTime = clock.getElapsedTime().asSeconds();
		ellapsedTime = clock.restart().asSeconds();
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window.pollEvent(event))
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();
			

		}

		
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
		player.move(mousePosition, deltaTime);

		ball.move(ellapsedTime);
		
		ball.manageCollisionWith(player, window);

		for (int i = 0; i < bricks.size(); i++)
		{
			if (bricks[i]->isAlive())
			{
				bricks[i]->draw(window);
				ball.manageCollisionWithBrick(*bricks[i]);
			}
			else
			{
				bricks[i]->destroyAndDelete(bricks);
			}
		}
		
		
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
		for (Brick* brick : bricks)
		{
			if (brick->isAlive())
			{
				brick->draw(window);
			}
		}
		player.draw(window);
		window.display();
	}
	

	return 0;
}