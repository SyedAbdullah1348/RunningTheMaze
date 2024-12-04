//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
//#include <iostream>
//#include <fstream>
//using namespace std;
//using namespace sf;
//
//
//int main()
//{
//	RenderWindow gameplay(VideoMode(1000, 500), "The Maze Runner : Level 1", Style::Default);
//	bool left = true, right = true, up = true, down = true;
//	char arr[10][20];
//
//
//	RectangleShape maze[10][20];
//
//	RectangleShape wall(Vector2f(50.f, 50.f)), floor(Vector2f(50.f, 50.f));
//	CircleShape pl(10.f);
//	Texture brick;
//	Texture grass;
//	brick.loadFromFile("brick.jpg");
//	grass.loadFromFile("grass2.jpg");
//	wall.setTexture(&brick);
//	floor.setTexture(&grass);
//	gameplay.setFramerateLimit(60);
//
//
//
//	string line;
//	ifstream file;
//	file.open("maze.txt");
//	for (int i = 0;i < 10;i++)
//	{
//		for (int j = 0;j < 20;j++)
//		{
//			file >> arr[i][j];
//			cout << arr[i][j] << " ";
//		}
//		cout << endl;
//	}
//
//	pl.setPosition(915, 60);
//
//	for (int i = 0;i < 10;i++)
//	{
//		for (int j = 0;j < 20;j++)
//		{
//			if (arr[i][j] == 'w')
//			{
//				maze[i][j] = wall;
//				maze[i][j].setPosition(j * 50, i * 50);
//			}
//			else if (arr[i][j] == 'f')
//			{
//				maze[i][j] = floor;
//				maze[i][j].setPosition(j * 50, i * 50);
//			}
//		}
//	}
//
//	while (gameplay.isOpen())
//	{
//		Event evnt;
//		while (gameplay.pollEvent(evnt))
//		{
//			if (evnt.type == Event::Closed)
//			{
//				gameplay.close();
//				return 0;
//			}
//			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
//				gameplay.close();
//		}
//
//		//Movements 
//
//		if ((pl.getPosition().x + 20 >= 950.f) || (pl.getPosition().x + 20 == 900.f && pl.getPosition().y >= 100) || (pl.getPosition().x + 20 == 800.f && pl.getPosition().y <= 400) || (pl.getPosition().x + 20 == 700.f && pl.getPosition().y + 20 >= 100) || (pl.getPosition().x + 20 == 600.f && pl.getPosition().y <= 400) || (pl.getPosition().x + 20 == 500.f && pl.getPosition().y + 20 >= 100) || (pl.getPosition().x + 20 == 400.f && pl.getPosition().y <= 400) || (pl.getPosition().x + 20 == 300.f && pl.getPosition().y >= 100) || (pl.getPosition().x + 20 == 200.f && pl.getPosition().y <= 400) || (pl.getPosition().x + 20 == 100.f && pl.getPosition().y >= 100))
//			right = false;
//		else
//			right = true;
//		if ((pl.getPosition().x <= 50.f) || (pl.getPosition().x == 850.f && pl.getPosition().y <= 400))
//			left = false;
//		else
//			left = true;
//		if ((pl.getPosition().y + 20 >= 450.f))
//			down = false;
//		else
//			down = true;
//		if ((pl.getPosition().y <= 50.f))
//			up = false;
//		else
//			up = true;
//
//		if (right == true && Keyboard::isKeyPressed(Keyboard::Key::Right))
//			pl.move(5.f, 0.f);
//		if (left == true && Keyboard::isKeyPressed(Keyboard::Key::Left))
//			pl.move(-5.f, 0.f);
//		if (up == true && Keyboard::isKeyPressed(Keyboard::Key::Up))
//			pl.move(0.f, -5.f);
//		if (down == true && Keyboard::isKeyPressed(Keyboard::Key::Down))
//			pl.move(0.f, 5.f);
//
//		gameplay.clear();
//
//		for (int i = 0;i < 10;i++)
//		{
//			for (int j = 0;j < 20;j++)
//			{
//				gameplay.draw(maze[i][j]);
//			}
//		}
//
//		gameplay.draw(pl);
//		gameplay.display();
//
//		if (Keyboard::isKeyPressed(Keyboard::Key::Space))
//		{
//			RenderWindow pause(VideoMode(1000, 500), "Paused", Style::Default);
//
//			while (pause.isOpen())
//			{
//				pause.setFramerateLimit(60);
//				RectangleShape pa(Vector2f(20.f, 20.f));
//				if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
//					return 0;
//				else if (Keyboard::isKeyPressed(Keyboard::Key::P))
//				{
//					pause.close();
//				}
//				pause.draw(pa);
//				pause.display();
//			}
//		}
//	}
//	return 0;
//}