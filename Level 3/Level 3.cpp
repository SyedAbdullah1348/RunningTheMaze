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

    //Auto maximise
    VideoMode desktopMode = VideoMode::getDesktopMode();
    gameplay.setSize(Vector2u(desktopMode.width - 2, desktopMode.height - 39));
    gameplay.setPosition(Vector2i(-7, -33));



    char arr[17][29];
    RectangleShape maze[17][29];

    //Gameover flag
    bool gameOver = false;

    //Font
    Font font;
    font.loadFromFile("KnightWarrior.otf");

    //Sprites
    RectangleShape wall(Vector2f(35.f, 35.f)), floor(Vector2f(35.f, 35.f)), start(Vector2f(35.f, 35.f)),end(Vector2f(35.f, 35.f)), 
        trap(Vector2f(35.f, 35.f)), background(Vector2f(1015, 595)), spikeTrap(Vector2f(35.f, 35.f)), torch(Vector2f(35.f, 35.f));

    CircleShape player(10.f);

    // Set initial player position
    player.setPosition(37.5f, 525.5f);

    //Set Textures
    Texture brick, grass, stFlag, endflag, pl, fireTrap, bg, spTrap, flame;
    brick.loadFromFile("black2.jpg");
    grass.loadFromFile("red.jpg");
    stFlag.loadFromFile("go.png");
    endflag.loadFromFile("endflag.png");
    fireTrap.loadFromFile("lava.jpeg");
    bg.loadFromFile("cemetary.jpeg");
    pl.loadFromFile("Kirby.jpg");
    spTrap.loadFromFile("spike.jpeg");
    flame.loadFromFile("torrch2.jpeg");

    wall.setTexture(&brick);
    floor.setTexture(&grass);
    start.setTexture(&stFlag);
    end.setTexture(&endflag);
    player.setTexture(&pl);
    trap.setTexture(&fireTrap);
    background.setTexture(&bg);
    spikeTrap.setTexture(&spTrap);
    torch.setTexture(&flame);


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
            else if (arr[i][j] == 'g')
                maze[i][j] = floor;
            else if (arr[i][j] == 'o')
                maze[i][j] = torch;

            maze[i][j].setPosition(j * 35, i * 35);
        }
    }

    //Trap boolean
    int thisTrap = 0;

    //Clock timer
    Clock clock;
    Clock trapClock;
    Clock jumpClock;

    //Pause time
    Time pauseTime = Time::Zero; // Total accumulated pause time
    
    

    

    //Main loop
    while (gameplay.isOpen() && gameOver == false) 
    {
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

        
        //Main game Timer
        Time time = clock.getElapsedTime() - pauseTime;
        
        Text timer;
        timer.setFont(font);
        timer.setString(to_string(time.asSeconds()));
        timer.setPosition(450.f, 0.f);
        cout << time.asSeconds() << endl;
        


        // Player movement flags
        bool left = true, right = true, up = true, down = true;


        // Collision detection + Stop movement altogether


        for (int i = 0; i < 17; i++) 
        {
            for (int j = 0; j < 29; j++) 
            {
                if (arr[i][j] == 'w') 
                {
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

        //Fire Traps
        
        
        Time trapTime = trapClock.getElapsedTime();
        int count = 0;
        if (trapTime.asSeconds() > 1.0f)
        {
            
            for (int i = 0; i < 17; i++)
            {
                for (int j = 0; j < 29; j++)
                {
                    if (arr[i][j] == 't')
                    {
                        count++;
                        if (thisTrap == 0)
                        {
                            
                            maze[i][j] = floor;
                            maze[i][j].setPosition(j * 35, i * 35);
                        }
                        else
                        {
                            
                            maze[i][j] = trap;
                            maze[i][j].setPosition(j * 35, i * 35);
                        }
                        
                    }
                }
            }
            if (count == 12)
            {
                trapClock.restart();
                if (thisTrap == 0)
                {
                    thisTrap = 1;
                }
                else
                    thisTrap = 0;
            }
        }

        //Player and fire trap collision
        for (int i = 0;i < 17;i++)
        {
            for (int j = 0;j < 29;j++)
            {
                if(arr[i][j] == 't' && thisTrap == 0)
                {
                    if (player.getPosition().x > maze[i][j].getPosition().x && player.getPosition().x + 20 <= maze[i][j+1].getPosition().x 
                        && player.getPosition().y > maze[i][j].getPosition().y && player.getPosition().y + 20 <= maze[i+1][j].getPosition().y)
                    {
                        lives--;
                        cout << "You have " << lives << " lives remaining." << endl;
                        player.setPosition(player.getPosition().x - 35, player.getPosition().y - 35);
                    }
                }
            }
        }
        
        //Spike Traps
       
        for (int i = 0; i < 17;i++)
        {
            for (int j = 0;j < 29;j++)
            {
                if (arr[i][j] == 'g')
                {
                    
                    //Triggering the trap
                    if ((player.getPosition().x + 20 >= maze[i][j - 1].getPosition().x) && (player.getPosition().x <= maze[i][j + 1].getPosition().x + 35) 
                        && (player.getPosition().y + 20 >= maze[i - 1][j].getPosition().y) && (player.getPosition().y <= maze[i + 1][j].getPosition().y + 35))
                    {
                        maze[i][j] = spikeTrap;
                        maze[i][j].setPosition(j * 35, i * 35);
                    }

                    //Player collides with trap

                    if ((player.getPosition().x + 20 > maze[i][j].getPosition().x) &&
                        (player.getPosition().x < maze[i][j].getPosition().x + 35) &&
                        (player.getPosition().y + 20 > maze[i][j].getPosition().y) &&
                        (player.getPosition().y < maze[i][j].getPosition().y + 35))
                    {
                        lives--;
                        std::cout << "You have " << lives << " lives remaining." << std::endl;

                        
                        if (player.getPosition().x + 20 > maze[i][j].getPosition().x && player.getPosition().x < maze[i][j].getPosition().x)
                        {
                            player.setPosition(maze[i][j].getPosition().x - 45, player.getPosition().y);
                        }
                        else if (player.getPosition().x < maze[i][j].getPosition().x + 35 && player.getPosition().x + 20 > maze[i][j].getPosition().x + 35)
                        {
                            player.setPosition(maze[i][j].getPosition().x + 60, player.getPosition().y);
                        }
                        else if (player.getPosition().y + 20 > maze[i][j].getPosition().y && player.getPosition().y < maze[i][j].getPosition().y)
                        {
                            player.setPosition(player.getPosition().x, maze[i][j].getPosition().y - 45);
                        }
                        else if (player.getPosition().y < maze[i][j].getPosition().y + 35 && player.getPosition().y + 20 > maze[i][j].getPosition().y + 35)
                        {
                            player.setPosition(player.getPosition().x, maze[i][j].getPosition().y + 60);
                        }
                    }
                }
            }
        }

        


        //Losing condition

        if (lives == 0)
        {
            cout << "YOU DIED! :(" << endl;

            gameOver = true;

            RenderWindow endgame(VideoMode(1015, 595), "GameOver", Style::Default);
            endgame.setFramerateLimit(60);

            endgame.setSize(Vector2u(desktopMode.width - 2, desktopMode.height - 35));
            endgame.setPosition(Vector2i(-7, -40));

            RectangleShape background(Vector2f(1015.f, 595.f));
            Texture bg;
            bg.loadFromFile("background2.jpg");
            background.setTexture(&bg);

            Text gameover, menu, exit, restart;

            //Gameover
            gameover.setFont(font);
            gameover.setCharacterSize(150);
            gameover.setPosition(235.f, 50.f);
            gameover.setString("GAME OVER");

            //Restart
            restart.setFont(font);
            restart.setCharacterSize(30);
            restart.setPosition(365.f, 250.f);
            restart.setString("Press R to restart level");

            //Menu
            menu.setFont(font);
            menu.setCharacterSize(30);
            menu.setPosition(365.f, 350.f);
            menu.setString("Press M to enter Main Menu");

            //Exit
            exit.setFont(font);
            exit.setCharacterSize(30);
            exit.setPosition(365.f, 450.f);
            exit.setString("Press Esc to exit");

            while (endgame.isOpen())
            {
                Event evnt;;
                while (endgame.pollEvent(evnt))
                {
                    if (evnt.type == Event::Closed)
                    {
                        endgame.close();
                        return 0;
                    }

                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
                {
                    gameOver = true;
                    endgame.close();
                }
                else if (Keyboard::isKeyPressed(Keyboard::Key::R))
                {
                    gameOver = false;
                    lives = 3;
                    player.setPosition(37.5f, 525.5f);
                    clock.restart();
                    endgame.close();


                }
                else if (Keyboard::isKeyPressed(Keyboard::Key::M))
                {
                    ;
                }
                endgame.clear();
                endgame.draw(background);
                endgame.draw(gameover);
                endgame.draw(restart);
                endgame.draw(menu);
                endgame.draw(exit);
                endgame.display();
            }
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


        // Jump functionality
        Time jumpTime = jumpClock.getElapsedTime();
        int playerX = player.getPosition().x / 35;
        int playerY = player.getPosition().y / 35;

        if (jumpTime.asSeconds() > 0.5 && Keyboard::isKeyPressed(Keyboard::Key::Space))
        {
            jumpClock.restart();
            if (arr[playerY][playerX - 1] == 'g')
                player.move(-70.f, 0.f);
            if (arr[playerY][playerX + 1] == 'g')
                player.move(70.f, 0.f);
            if (arr[playerY + 1][playerX] == 'g')
                player.move(0.f, 70.f);
            if (arr[playerY - 1][playerX] == 'g')
                player.move(0.f, -70.f);
        }

        
        

        
        gameplay.clear();
        for (int i = 0; i < 17; i++) {
            for (int j = 0; j < 29; j++) {
                gameplay.draw(maze[i][j]);
            }
        }
        gameplay.draw(timer);
        gameplay.draw(player);
        gameplay.display();

        ////Jump functionality
        //
        //int playerX = player.getPosition().x / 35;
        //int playerY = player.getPosition().y / 35;
        //bool isNearSpikeTrap = false;
        //while(isNearSpikeTrap == false && Keyboard::isKeyPressed(Keyboard::Key::Space))
        //{
        //   
        //    if (arr[playerX + 1][playerY] == 'g' || arr[playerX - 1][playerY] == 'g')
        //    {
        //        player.move(70.f, 0.f);
        //        /*if (Keyboard::isKeyPressed(Keyboard::Key::Right) || Keyboard::isKeyPressed(Keyboard::Key::D))
        //            player.move(3.f, 0.f);
        //        if (Keyboard::isKeyPressed(Keyboard::Key::Left) || Keyboard::isKeyPressed(Keyboard::Key::A))
        //            player.move(-3.f, 0.f);
        //        if (Keyboard::isKeyPressed(Keyboard::Key::Up) || Keyboard::isKeyPressed(Keyboard::Key::W))
        //            player.move(0.f, -3.f);
        //        if (Keyboard::isKeyPressed(Keyboard::Key::Down) || Keyboard::isKeyPressed(Keyboard::Key::S))
        //            player.move(0.f, 3.f);*/
        //    }
        //    
        //    
        //    gameplay.clear();
        //    for (int i = 0; i < 17; i++) {
        //        for (int j = 0; j < 29; j++) {
        //            gameplay.draw(maze[i][j]);
        //        }
        //    }
        //    gameplay.draw(timer);
        //    gameplay.draw(player);
        //    gameplay.display();
        //}

        

        //Draw

        gameplay.clear();

        for (int i = 0; i < 17; i++) {
            for (int j = 0; j < 29; j++) {
                gameplay.draw(maze[i][j]);
            }
        }
        gameplay.draw(timer);
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

        if (Keyboard::isKeyPressed(Keyboard::Key::P))
        {
            
            
            Clock pauseClock;            // Tracks duration of current pause

            RenderWindow pause(VideoMode(1015, 595), "Paused", Style::Default);
            pause.setFramerateLimit(60);

            pause.setSize(Vector2u(desktopMode.width - 2, desktopMode.height - 35));
            pause.setPosition(Vector2i(-7, -40));

            RectangleShape background(Vector2f(1015.f, 595.f));
            Texture bg;
            bg.loadFromFile("background.jpg");
            background.setTexture(&bg);

            Text paused, resume, menu, exit, restart;

            //Paused
            paused.setFont(font);
            paused.setCharacterSize(100);
            paused.setPosition(235.f, 50.f);
            paused.setString("Game Paused");

            //Resume
            resume.setFont(font);
            resume.setCharacterSize(30);
            resume.setPosition(300.f, 200.f);
            resume.setString("Press Enter to resume level");

            //Restart
            restart.setFont(font);
            restart.setCharacterSize(30);
            restart.setPosition(300.f, 300.f);
            restart.setString("Press R to restart level");

            //Menu
            menu.setFont(font);
            menu.setCharacterSize(30);
            menu.setPosition(300.f, 400.f);
            menu.setString("Press M to enter Main Menu");

            //Exit
            exit.setFont(font);
            exit.setCharacterSize(30);
            exit.setPosition(300.f, 500.f);
            exit.setString("Press Esc to exit");

            while (pause.isOpen())
            {
                Event evnt;
                while (pause.pollEvent(evnt)) {
                    if (evnt.type == Event::Closed) {
                        return 0;
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
                        pause.close();
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
                        // Accumulate pause time and close pause menu
                        pauseTime += pauseClock.getElapsedTime();
                        //pauseClock.restart();
                        pause.close();
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Key::R)) {
                        gameOver = false;
                        lives = 3;
                        player.setPosition(37.5f, 525.5f);
                        clock.restart();
                        pauseTime = Time::Zero; // Reset pause time
                        pause.close();
                    }
                }
                
                pause.clear();
                pause.draw(background);
                pause.draw(paused);
                pause.draw(resume);
                pause.draw(restart);
                pause.draw(menu);
                pause.draw(exit);
                pause.display();
            }
        }
    }

    return 0;
}
