#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

int main()
{

    // Declarations

    int lives = 3;
    cout << "You have " << lives << " lives remaining." << endl;
    RenderWindow gameplay(VideoMode(1015, 595), "The Maze Runner : Level 3", Style::Default);
    gameplay.setFramerateLimit(60);

    char arr[17][29];

    RectangleShape maze[17][29];
    
    RectangleShape wall(Vector2f(35.f, 35.f)), floor(Vector2f(35.f, 35.f)), start(Vector2f(35.f, 35.f)),
        end(Vector2f(35.f, 35.f)), trap(Vector2f(35.f, 35.f));
    
    CircleShape player(10.f);

    // Set initial player position
    player.setPosition(37.5f, 525.5f);

    //Set Textures
    Texture brick, grass, stFlag, endflag, pl, firetrap;
    brick.loadFromFile("wood.jpeg");
    grass.loadFromFile("grass2.jpg");
    stFlag.loadFromFile("go.png");
    endflag.loadFromFile("endflag.png");
    firetrap.loadFromFile("lava.jpeg");
    pl.loadFromFile("Kirby.jpg");
    wall.setTexture(&brick);
    floor.setTexture(&grass);
    start.setTexture(&stFlag);
    end.setTexture(&endflag);
    player.setTexture(&pl);
    trap.setTexture(&firetrap);

    

    // Load maze from file
    ifstream file("maze.txt");
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 29; j++) {
            file >> arr[i][j];
        }
    }
    file.close();
    

    // Initialize maze tiles
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 29; j++) {
            if (arr[i][j] == 'w') {
                maze[i][j] = wall;
            }
            else if (arr[i][j] == 'f') {
                maze[i][j] = floor;
            }
            else if (arr[i][j] == 's') {
                maze[i][j] = start;
            }
            else if (arr[i][j] == 'e') {
                maze[i][j] = end;
            }
            else if (arr[i][j] == 't')
                maze[i][j] = trap;
            maze[i][j].setPosition(j * 35, i * 35);
        }
    }



    //Main loop
    while (gameplay.isOpen()) {
        Event evnt;
        while (gameplay.pollEvent(evnt)) {
            if (evnt.type == Event::Closed) {
                gameplay.close();
                return 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
                gameplay.close();
            }
        }

        // Player movement flags
        bool left = true, right = true, up = true, down = true;

        //Gameover flag
        bool gameOver = false;

        // Collision detection + Stop movement altogether


        for (int i = 0; i < 17; i++) {
            for (int j = 0; j < 29; j++) {
                if (arr[i][j] == 'w') {
                    // Wall positions
                    float wallLeft = maze[i][j].getPosition().x;
                    float wallRight = wallLeft + 35;
                    float wallTop = maze[i][j].getPosition().y;
                    float wallBottom = wallTop + 35;

                    // Player positions
                    float playerLeft = player.getPosition().x;
                    float playerRight = playerLeft + 20; 
                    float playerTop = player.getPosition().y;
                    float playerBottom = playerTop + 20;

                    if (playerRight > wallLeft && playerLeft < wallRight && playerTop < wallBottom && playerBottom > wallTop) {
                        if (playerLeft < wallRight && playerRight > wallLeft) 
                        {
                            if (playerBottom > wallTop && playerTop < wallTop) 
                            {
                                down = false;
                            }
                            if (playerTop < wallBottom && playerBottom > wallBottom) 
                            {
                                up = false;
                            }
                        }
                        if (playerBottom > wallTop && playerTop < wallBottom) 
                        {
                            if (playerRight > wallLeft && playerLeft < wallLeft) 
                            {
                                right = false;
                            }
                            if (playerLeft < wallRight && playerRight > wallRight) 
                            {
                                left = false;
                            }
                        }
                    }
                }
            }
        }

        //Traps
        if (player.getPosition().x > 19 * 35 && player.getPosition().x < 20 * 35 && player.getPosition().y > 14 * 35 && player.getPosition().y < 15 * 35)
        {
            cout << "gaeeeeeeeeeeeeee" << endl;
            lives--;
            cout << "You have " << lives << " lives remaining." << endl;
            player.setPosition(Vector2f(18 * 35, 13 * 35));
        }
        if (lives == 0)
        {
            cout << "YOU DIED! :(" << endl;
            gameOver = true;
            
        }



        // Player movement
        if (right && (Keyboard::isKeyPressed(Keyboard::Key::Right) || Keyboard::isKeyPressed(Keyboard::Key::D)))
            player.move(3.f, 0.f);
        if (left && (Keyboard::isKeyPressed(Keyboard::Key::Left) || Keyboard::isKeyPressed(Keyboard::Key::A)))
            player.move(-3.f, 0.f);
        if (up && (Keyboard::isKeyPressed(Keyboard::Key::Up) || Keyboard::isKeyPressed(Keyboard::Key::W)))
            player.move(0.f, -3.f);
        if (down && (Keyboard::isKeyPressed(Keyboard::Key::Down) || Keyboard::isKeyPressed(Keyboard::Key::S)))
            player.move(0.f, 3.f);

        gameplay.clear();

        for (int i = 0; i < 17; i++) {
            for (int j = 0; j < 29; j++) {
                gameplay.draw(maze[i][j]);
            }
        }

        gameplay.draw(player);
        gameplay.display();

        // Check win condition
        if (player.getPosition().y + 10 <= 490.f && player.getPosition().y + 10 >= 455.f &&
            player.getPosition().x + 10 < 840 && player.getPosition().x > 805) 
        {
            cout << "NISHAN E AQAL WALON K LIYE KAAFI HAI!!!!" << endl;
            return 0;
        }


        //Pause game

        if (Keyboard::isKeyPressed(Keyboard::Key::Space))
		{
			RenderWindow pause(VideoMode(1015, 595), "Paused", Style::Default);
            pause.setFramerateLimit(60);

			while (pause.isOpen())
            {
                Event evnt;
                while (pause.pollEvent(evnt)) {
                    if (evnt.type == Event::Closed) {
                        pause.close();
                        return 0;
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
                        pause.close();
                        return 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Key::P))
                    {
                        pause.close();
                    }
                }
				RectangleShape pa(Vector2f(20.f, 20.f));
			
				pause.draw(pa);
				pause.display();
			}
		}
	}
    return 0;
}
