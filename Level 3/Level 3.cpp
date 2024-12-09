#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace sf;


int main()
{
    VideoMode desktopMode = VideoMode::getDesktopMode();
    RenderWindow gameplay(VideoMode(1160, 680), "The Maze Runner : Level 3", Style::Default);
    gameplay.setFramerateLimit(60);

    //Auto maximise
    gameplay.setSize(Vector2u(desktopMode.width - 2, desktopMode.height - 39));
    gameplay.setPosition(Vector2i(-7, -33));
    //Audio
    SoundBuffer bgB, fireB, sizzleB, spikeB, jumpB, gameoverB, pauseB, c;

    bgB.loadFromFile("audio/melancholia.mp3");
    fireB.loadFromFile("audio/fire.mp3");
    sizzleB.loadFromFile("audio/sizzle.mp3");
    spikeB.loadFromFile("audio/spike.mp3");
    jumpB.loadFromFile("audio/jump2.mp3");
    gameoverB.loadFromFile("audio/gameover.mp3");
    pauseB.loadFromFile("audio/pause.mp3");
    c.loadFromFile("audio/coin.mp3");


    Sound bgS, fireS, sizzleS, spikeS, jumpS, gameoverS, pauseS, coin;

    bgS.setBuffer(bgB);
    fireS.setBuffer(fireB);
    sizzleS.setBuffer(sizzleB);
    spikeS.setBuffer(spikeB);
    jumpS.setBuffer(jumpB);
    gameoverS.setBuffer(gameoverB);
    pauseS.setBuffer(pauseB);
    coin.setBuffer(c);

    int score = 0;
    float startX = 37.5f, startY = 600.f;
    bool resume = false;

    bool movetomenu = true;
    while (movetomenu = true)
    {
        //Main menu
       
        RenderWindow mainMenu(VideoMode(1160, 680), "Main Menu", Style::Default);
        mainMenu.setFramerateLimit(60);

        //Auto maximise
        mainMenu.setSize(Vector2u(desktopMode.width - 2, desktopMode.height - 39));
        mainMenu.setPosition(Vector2i(-7, -33));

        //Font
        Font font;
        font.loadFromFile("KnightWarrior.otf");

        RectangleShape background1(Vector2f(desktopMode.width, desktopMode.height));
        Texture bg;
        bg.loadFromFile("bg3.jpg");
        background1.setTexture(&bg);
        
        //Display resume text tracker

        string line;
        ifstream level3("Level 3.txt");
        level3 >> line;
        level3.close();

        // Audio
        SoundBuffer mm;
        Sound main;
        mm.loadFromFile("audio/lulllaby.mp3");
        main.setBuffer(mm);

        main.play();
        main.setLoop(true);

        Text title, resumeP, sng, controls, exitG;

        //Title
        title.setFont(font);
        title.setCharacterSize(70);
        title.setPosition(180.f, 100.f);
        title.setString("Shadow Runners");
        title.setFillColor(Color::Red);

        //Resume
        resumeP.setFont(font);
        resumeP.setCharacterSize(25);
        resumeP.setPosition(180.f, 300.f);
        resumeP.setString("Press R to resume from previous save");

        //Start new game
        sng.setFont(font);
        sng.setCharacterSize(25);
        sng.setPosition(180.f, 400.f);
        sng.setString("Press Enter to Start New Game");

        //Controls
        controls.setFont(font);
        controls.setCharacterSize(25);
        controls.setPosition(180.f, 500.f);
        controls.setString("Press C to show controls");

        //Exit
        exitG.setFont(font);
        exitG.setCharacterSize(25);
        exitG.setPosition(180.f, 600.f);
        exitG.setString("Press Esc to exit");

        while (mainMenu.isOpen() && resume == false)
        {
            Event evnt;
            while (mainMenu.pollEvent(evnt))
            {
                if (evnt.type == Event::Closed)
                {
                    return 0;
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
                {
                    return 0;
                }
                else if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
                {
                    mainMenu.close();
                    main.stop();
                }
                else if (Keyboard::isKeyPressed(Keyboard::Key::R))
                {
                    
                    if (line == "1")
                    {
                        resume = true;
                        mainMenu.close();
                        main.stop();
                    }
                }
                else if (Keyboard::isKeyPressed(Keyboard::Key::C))
                {

                    bool openC = true;
                    Texture c;
                    RectangleShape control(Vector2f(306.f,700.f));
                    control.setPosition(100.f, 50.f);
                    c.loadFromFile("controls.jpg");
                    control.setTexture(&c);
                    while (openC == true)
                    {
                        mainMenu.clear();
                        mainMenu.draw(background1);
                        mainMenu.draw(control);
                        mainMenu.display();
                        if (Keyboard::isKeyPressed(Keyboard::Key::E))
                        {
                            openC = false;
                        }
                    }
                }
            }



            mainMenu.clear();
            mainMenu.draw(background1);
            mainMenu.draw(title);
            if (line == "1")
            {
                mainMenu.draw(resumeP);
            }
            mainMenu.draw(sng);
            mainMenu.draw(controls);
            mainMenu.draw(exitG);
            mainMenu.display();
        }


        // Declarations

        int lives = 3;
        cout << "You have " << lives << " lives remaining." << endl;
        
        cout << gameplay.getSize().x << endl;


        char arr[17][29];
        RectangleShape maze[17][29];
        RectangleShape collectible[17][29];

        //Gameover flag
        bool gameOver = false;



        //Sprites
        RectangleShape wall(Vector2f(40.f, 40.f)), floor(Vector2f(40.f, 40.f)), start(Vector2f(40.f, 40.f)), end(Vector2f(40.f, 40.f)),
            trap(Vector2f(40.f, 40.f)), background(Vector2f(1015, 595)), spikeTrap(Vector2f(40.f, 40.f)), torchF(Vector2f(40.f, 40.f)), flame(Vector2f(40.f, 40.f)), skull(Vector2f(40.f, 40.f));

        Sprite player;
        Texture pl;
        pl.loadFromFile("sprite.png");
        player.setTexture(pl);
        float height = 320, width = 212.75;
        player.setTextureRect(IntRect(0.f, height* 3, width, height));
        player.setScale(30 / width, 30 / height);


        // Set initial player position
        player.setPosition(startX, startY);

        //Set Textures
        Texture brick, grass, stFlag, endflag, fireTrap, bg1, spTrap, torch, flameTexture, sk;
        brick.loadFromFile("black2.jpg");
        grass.loadFromFile("red.jpg");
        stFlag.loadFromFile("go.png");
        endflag.loadFromFile("endflag.png");
        fireTrap.loadFromFile("lava.jpeg");
        bg1.loadFromFile("cemetary.jpeg");
        spTrap.loadFromFile("spikey.png");
        torch.loadFromFile("torrch2.jpeg");
        flameTexture.loadFromFile("flame.jpg");
        sk.loadFromFile("skull.png");

        wall.setTexture(&brick);
        floor.setTexture(&grass);
        start.setTexture(&stFlag);
        end.setTexture(&endflag);
        trap.setTexture(&fireTrap);
        background.setTexture(&bg);
        spikeTrap.setTexture(&spTrap);
        torchF.setTexture(&torch);
        flame.setTexture(&flameTexture);
        skull.setTexture(&sk);


        // Animation variables
        const int frameWidth = 94.8;   // Width of each frame
        const int frameHeight = 145;  // Height of each frame
        const int numFrames = 15;     // Total number of frames
        const int framesPerRow = 5;   // Number of frames in each row of the sprite sheet
        Time frameDuration = sf::milliseconds(100); // Time per frame

        int currentFrames[17][29] = { 0 };   // Raw array to track the current animation frame
        Clock animationClock;


        // Load maze from file
        ifstream file("maze.txt");
        for (int i = 0; i < 17; i++) 
        {
            for (int j = 0; j < 29; j++) 
            {
                file >> arr[i][j];
            }
        }
        file.close();


        // Initialize maze tiles
        for (int i = 0; i < 17; i++) 
        {
            for (int j = 0; j < 29; j++) 
            {
                if (arr[i][j] == 'w') 
                {
                    maze[i][j] = wall;
                }
                else if (arr[i][j] == 'f') 
                {
                    maze[i][j] = floor;
                    if (i % 2 == 0 || j % 2 == 0)
                    {
                        collectible[i][j] = skull;
                        collectible[i][j].setPosition(j * 40 + 10, i * 40 + 10);
                        collectible[i][j].setScale(0.5,0.5);
                    }
                }
                else if (arr[i][j] == 's') 
                {
                    maze[i][j] = start;
                }
                else if (arr[i][j] == 'e') 
                {
                    maze[i][j] = end;
                }
                else if (arr[i][j] == 't')
                    maze[i][j] = trap;
                else if (arr[i][j] == 'g')
                    maze[i][j] = floor;
                else if (arr[i][j] == 'o')
                    maze[i][j] = flame;

                maze[i][j].setPosition(j * 40, i * 40);
            }
        }

        

        //Trap trackers
        int thisTrap = 0;
        bool spikes = false;

        //Jump variables

        bool isJumping = false;
        Vector2f startPos;
        Vector2f targetPos;
        float jumpProgress = 0.0f;
        bool ignoreSpike = false;
        int playerX;
        int playerY;

        //Clock timer
        Clock clock;
        Clock trapClock;
        Clock jumpClock;
        Time time;

        //Pause time
        Time pauseTime = Time::Zero; //Total accumulated pause time

        

        bgS.play();
        fireS.play();

        //Resume functionality
        float prevTime = 0;
        string highscore = "0";


        
        ifstream levels3("Level 3.txt");
        levels3 >> line;
        levels3 >> highscore;

        if (resume == true)
        {
            levels3 >> score; // Load score
            levels3 >> startX; // Load player X position
            levels3 >> startY; // Load player Y position
            levels3 >> prevTime; // Load previous time

            // Load the maze array
            for (int i = 0; i < 17; i++) {
                for (int j = 0; j < 29; j++) {
                    levels3 >> arr[i][j];
                    cout << arr[i][j];
                }
                cout << endl;
            }
            player.setPosition(startX, startY);
        }
        levels3.close();
        

        //Main loop
        while (gameplay.isOpen() && gameOver == false)
        {
            Event evnt;
            while (gameplay.pollEvent(evnt))
            {

                if (evnt.type == Event::Closed)
                {
                    ofstream level3("Level 3.txt");

                    level3 << "1" << endl;
                    level3 << highscore << endl;
                    level3 << score << endl;
                    level3 << player.getPosition().x << endl;
                    level3 << player.getPosition().y << endl;
                    level3 << to_string(time.asSeconds() + prevTime) << endl;
                    for (int i = 0;i < 17;i++)
                    {
                        for (int j = 0;j < 29;j++)
                        {
                            level3 << arr[i][j];
                        }
                        level3 << endl;
                    }
                    level3.close();
                    gameplay.close();
                    movetomenu = false;
                    return 0;
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
                {
                    ofstream level3("Level 3.txt");
                    level3 << "1" << endl;
                    level3 << highscore << endl;
                    level3 << score << endl;
                    level3 << player.getPosition().x << endl;
                    level3 << player.getPosition().y << endl;
                    level3 << to_string(time.asSeconds() + prevTime) << endl;
                    for (int i = 0; i < 17; i++)
                    {
                        for (int j = 0; j < 29; j++)
                        {
                            level3 << arr[i][j];
                        }
                        level3 << endl;
                    }
                    level3.close();
                    gameplay.close();
                    return 0;
                }
            }


            //Score
            Text scoreT;
            scoreT.setFont(font);
            scoreT.setString("Your score is : " + to_string(score));


            // Update animation for each flame
            if (animationClock.getElapsedTime() > frameDuration) {
                for (int row = 0; row < 17; ++row) {
                    for (int col = 0; col < 29; ++col) {
                        if (arr[row][col] == 'o' && (row == 0 || col == 0 || row == 16 || col == 28))
                        {
                            // Update the current frame
                            currentFrames[row][col] = (currentFrames[row][col] + 1) % numFrames;

                            // Calculate the texture rectangle
                            int x = (currentFrames[row][col] % framesPerRow) * frameWidth; // Column in the sprite sheet
                            int y = (currentFrames[row][col] / framesPerRow) * frameHeight; // Row in the sprite sheet
                            maze[row][col].setTextureRect(sf::IntRect(x, y, frameWidth, frameHeight));
                        }
                    }
                }
                animationClock.restart();
            }

            //Main game Timer

            time = clock.getElapsedTime() - pauseTime;

            Text timer;
            timer.setFont(font);
            timer.setString(to_string(time.asSeconds() + prevTime));
            timer.setPosition(450.f, 0.f);



            // Player movement flags
            bool left = true, right = true, up = true, down = true;


            // Collision detection + Stop movement altogether
            for (int i = 0; i < 17; i++) {
                for (int j = 0; j < 29; j++) {
                    if (arr[i][j] == 'w' || arr[i][j] == 'o') {  // Check for walls or obstacles
                        // Wall positions
                        float wallLeft = maze[i][j].getPosition().x + 5;
                        float wallRight = wallLeft + 30;
                        float wallTop = maze[i][j].getPosition().y + 5;
                        float wallBottom = wallTop + 30;

                        // Player positions
                        float playerLeft = player.getPosition().x + 10;
                        float playerRight = playerLeft + 20;  // Assuming player's width is 30
                        float playerTop = player.getPosition().y + 10;
                        float playerBottom = playerTop + 30;  // Assuming player's height is 30

                        // Check for horizontal collision (left and right)
                        if (playerBottom > wallTop && playerTop < wallBottom) { // Only check horizontal if vertical overlap
                            if (playerRight > wallLeft && playerLeft < wallLeft) { // Colliding from the left
                                right = false;  // Prevent rightward movement
                            }
                            else if (playerLeft < wallRight && playerRight > wallRight) { // Colliding from the right
                                left = false;  // Prevent leftward movement
                            }
                        }

                        // Check for vertical collision (up and down)
                        if (playerRight > wallLeft && playerLeft < wallRight) { // Only check vertical if horizontal overlap
                            if (playerBottom > wallTop && playerTop < wallTop) { // Colliding from above
                                down = false;  // Prevent downward movement
                            }
                            else if (playerTop < wallBottom && playerBottom > wallBottom) { // Colliding from below
                                up = false;  // Prevent upward movement
                            }
                        }
                    }
                }
            }


            // Player movement

            if (right && (Keyboard::isKeyPressed(Keyboard::Key::Right) || Keyboard::isKeyPressed(Keyboard::Key::D)))
            {
                int xTexture = 0;
                xTexture = (int)player.getPosition().x / 30 % 4;
                player.setTextureRect(IntRect(xTexture * width, height * 2, width, height));
                player.move(3, 0);
            }
            if (left && (Keyboard::isKeyPressed(Keyboard::Key::Left) || Keyboard::isKeyPressed(Keyboard::Key::A)))
            {
                int xTexture = 0;
                xTexture = (int)player.getPosition().x / 30 % 4;
                player.setTextureRect(IntRect(xTexture * width, height, width, height));
                player.move(-3, 0);
            }
            if (up && (Keyboard::isKeyPressed(Keyboard::Key::Up) || Keyboard::isKeyPressed(Keyboard::Key::W)))
            {
                int xTexture = 0;
                xTexture = (int)player.getPosition().y / 30 % 4;
                player.setTextureRect(IntRect(xTexture * width, height * 3, width, height));
                player.move(0, -3);
            }
            if (down && (Keyboard::isKeyPressed(Keyboard::Key::Down) || Keyboard::isKeyPressed(Keyboard::Key::S)))
            {
                int xTexture = 0;
                xTexture = (int)player.getPosition().y / 30 % 4;
                player.setTextureRect(IntRect(xTexture * width, 0.f, width, height));
                player.move(0, 3);
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
                                maze[i][j].setPosition(j * 40, i * 40);
                            }
                            else
                            {

                                maze[i][j] = trap;
                                maze[i][j].setPosition(j * 40, i * 40);
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
                    if (thisTrap == 0 && arr[i][j] == 't' && ((player.getPosition().x + 20 > maze[i][j].getPosition().x) &&
                        (player.getPosition().x + 15 < maze[i][j].getPosition().x + 40) &&
                        (player.getPosition().y + 20 > maze[i][j].getPosition().y) &&
                        (player.getPosition().y + 10 < maze[i][j].getPosition().y + 40)))

                    {
                        lives--;
                        std::cout << "You have " << lives << " lives remaining." << std::endl;
                        sizzleS.play();

                        if (player.getPosition().x + 30 > maze[i][j].getPosition().x && player.getPosition().x < maze[i][j].getPosition().x)
                        {
                            player.setPosition(maze[i][j].getPosition().x - 50, player.getPosition().y);
                        }
                        else if (player.getPosition().x + 10 < maze[i][j].getPosition().x + 40 && player.getPosition().x + 30 > maze[i][j].getPosition().x + 40)
                        {
                            player.setPosition(maze[i][j].getPosition().x + 60, player.getPosition().y);
                        }

                        else if (player.getPosition().y + 30 > maze[i][j].getPosition().y && player.getPosition().y < maze[i][j].getPosition().y)
                        {
                            player.setPosition(player.getPosition().x, maze[i][j].getPosition().y - 50);
                        }
                        else if (player.getPosition().y < maze[i][j].getPosition().y + 40 && player.getPosition().y + 30 > maze[i][j].getPosition().y + 40)
                        {
                            player.setPosition(player.getPosition().x, maze[i][j].getPosition().y + 60);
                        }
                    }
                }
            }

            //Spike Traps

            if (spikes == false)
            {
                for (int i = 0;i < 17;i++)
                {
                    for (int j = 0;j < 29;j++)
                    {
                        if (arr[i][j] == 'g')
                            maze[i][j] = floor;
                        maze[i][j].setPosition(j * 40, i * 40);
                    }
                }
            }

            //Trigger and collision

            for (int i = 0; i < 17;i++)
            {
                for (int j = 0;j < 29;j++)
                {
                    if (arr[i][j] == 'g')
                    {

                        //Triggering the trap
                        if ((player.getPosition().x + 10 >= maze[i][j - 1].getPosition().x) && (player.getPosition().x + 5 <= maze[i][j + 1].getPosition().x + 30)
                            && (player.getPosition().y + 10 >= maze[i - 1][j].getPosition().y) && (player.getPosition().y + 5 <= maze[i + 1][j].getPosition().y + 30))
                        {
                            spikeS.play();
                            spikes = true;
                            maze[i][j] = spikeTrap;
                            maze[i][j].setPosition(j * 40, i * 40);
                        }

                        //Player collides with trap

                        if (ignoreSpike == false && ((player.getPosition().x + 20 > maze[i][j].getPosition().x) &&
                            (player.getPosition().x + 10 < maze[i][j].getPosition().x + 30) &&
                            (player.getPosition().y + 30 > maze[i][j].getPosition().y) &&
                            (player.getPosition().y + 10 < maze[i][j].getPosition().y + 30)))
                        {


                            lives--;
                            std::cout << "You have " << lives << " lives remaining." << std::endl;
                            spikeS.play();

                            if (player.getPosition().x + 20 > maze[i][j].getPosition().x && player.getPosition().x + 10 < maze[i][j].getPosition().x)
                            {

                                player.setPosition(maze[i][j].getPosition().x - 45, player.getPosition().y);
                            }
                            else if (player.getPosition().x + 10 < maze[i][j].getPosition().x + 30 && player.getPosition().x + 20 > maze[i][j].getPosition().x + 30)
                            {

                                player.setPosition(maze[i][j].getPosition().x + 60, player.getPosition().y);
                            }

                            else if (player.getPosition().y + 30 > maze[i][j].getPosition().y && player.getPosition().y < maze[i][j].getPosition().y)
                            {

                                player.setPosition(player.getPosition().x, maze[i][j].getPosition().y - 70);
                            }
                            else if (player.getPosition().y + 10 < maze[i][j].getPosition().y + 30 && player.getPosition().y + 20 > maze[i][j].getPosition().y + 30)
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
                gameoverS.play();

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
                            ofstream level3("Level 3.txt");
                            level3 << "0" << endl;
                            level3.close();
                            endgame.close();
                            return 0;
                        }

                    }
                    if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
                    {
                        ofstream level3("Level 3.txt");
                        level3 << "0" << endl;
                        level3.close();
                        gameOver = true;
                        movetomenu = false;
                        endgame.close();
                        return 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Key::R))
                    {
                        gameOver = false;
                        lives = 3;
                        spikes = false;
                        player.setPosition(37.5f, 600.f);
                        clock.restart();
                        endgame.close();
                        resume = false;
                        score = 0;

                        //Re-initialize collectbles

                        for (int i = 0;i < 17;i++)
                        {
                            for (int j = 0;j < 29;j++)
                            {
                                if (arr[i][j] == 'z')
                                {
                                    arr[i][j] = 'f';
                                }
                            }
                        }

                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Key::M))
                    {
                        ofstream level3("Level 3.txt");
                        level3 << "0" << endl;
                        level3.close();
                        endgame.close();
                        gameplay.close();
                        movetomenu = true;
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

            //Collectibles

            playerX = (player.getPosition().x + 15) / 40;
            playerY = (player.getPosition().y + 30) / 40;

            if (arr[playerY][playerX] == 'f' && (playerY % 2 == 0 || playerX % 2 == 0))
            {
                arr[playerY][playerX] = 'z';
                score += 50;
                coin.play();
            }


            //Jump functionality

            Time jumpTime = jumpClock.getElapsedTime();


            if (isJumping == false && jumpTime.asSeconds() > 0.5 && Keyboard::isKeyPressed(Keyboard::Key::Space))
            {
                jumpClock.restart();
                jumpS.play();

                playerX = (player.getPosition().x + 15) / 40;
                playerY = (player.getPosition().y + 30) / 40;
                startPos = player.getPosition();

                if (arr[playerY][playerX - 1] == 'g' && playerX > 0)
                {
                    jumpS.play();
                    targetPos = startPos + Vector2f(-80.f, 0.f);
                    isJumping = true;
                    ignoreSpike = true;
                }
                else if (arr[playerY][playerX + 1] == 'g' && playerX < 28)
                {
                    jumpS.play();
                    targetPos = startPos + Vector2f(80.f, 0.f);
                    isJumping = true;
                    ignoreSpike = true;
                }
                else if (arr[playerY + 1][playerX] == 'g' && playerY < 16)
                {
                    jumpS.play();
                    targetPos = startPos + sf::Vector2f(0.f, 80.f);
                    isJumping = true;
                    ignoreSpike = true;
                }
                else if (arr[playerY - 1][playerX] == 'g' && playerY > 0)
                {
                    jumpS.play();
                    targetPos = startPos + sf::Vector2f(0.f, -80.f);
                    isJumping = true;
                    ignoreSpike = true;
                }

                jumpProgress = 0.0f;
            }

            if (isJumping)
            {
                jumpProgress += 0.05f;

                if (jumpProgress >= 1.0f)
                {
                    jumpProgress = 1.0f;
                    isJumping = false;
                    ignoreSpike = false;
                }


                Vector2f newPos = startPos + (targetPos - startPos) * jumpProgress;
                player.setPosition(newPos);
            }



            // Check win condition

            if (arr[playerY][playerX] == 'e')
            {
                ofstream level3("Level 3.txt");
                level3 << "0" << endl;
                if (score > stoi(highscore))
                {
                    level3 << score << endl;
                }
                else
                    level3 << highscore << endl;

                level3.close();
                cout << "NISHAN E AQAL WALON K LIYE KAAFI HAI!!!!!" << endl;

                RenderWindow win(VideoMode(1160, 680), "You can't win", Style::Default);
                win.setFramerateLimit(60);

                // Auto maximize
                VideoMode desktopMode = VideoMode::getDesktopMode();
                win.setSize(Vector2u(desktopMode.width - 2, desktopMode.height - 39));
                win.setPosition(Vector2i(-7, -33));

                Sound winS;
                SoundBuffer winB;
                winB.loadFromFile("audio/violin.mp3");
                winS.setBuffer(winB);
                bgS.stop();
                winS.play();
                

                // Dialogue lines
                vector<string> dialogues = 
                {
                    "You really thought you could win? How pathetic.",
                    "I’ve watched you stumble through my maze.", 
                    "Clinging to the foolish belief that you could outsmart me.",
                    "But every step you took, every choice you made.",
                    "It all led here.",
                    "Right where I wanted you.",
                    "You see, that’s the cruel truth you fail to grasp.",
                    "There was never any victory to claim.",
                    "You’re not the hero of some grand tale.",
                    " You’re a pawn, moved and discarded at my whim.",
                    "You fought so hard, endured so much.",
                    "All for nothing.",
                    "And now, here you stand, at the edge of oblivion.",
                    "Staring into the void I created for you.",
                    "This isn’t your story.",
                    "It never was.",
                    "It’s mine.",
                    " and it ends when I decide.",
                    "The truth is, the world won’t remember you.",
                    "No songs will be sung.",
                    "No statues will be raised.",
                    "Youll vanish",
                    "Nothing but a fleeting flicker of light.",
                    "You.",
                    "Are.",
                    "Nothing.",
                    "but you could be something.",
                    "Credits : ",
                    "Aliha Fatima Chaudhary",
                    "Ali Shahid Hassan Nawaz",
                    "Syed Abdullah",
                    "Special thanks to Sir Usama Hassan Alvi"
                };

                // Text object for displaying dialogue
                Text dialogueText;
                dialogueText.setFont(font);
                dialogueText.setCharacterSize(45);
                dialogueText.setFillColor(Color::Red);
                dialogueText.setPosition(30.f, 340.f);

                size_t dialogueIndex = 0;

                Clock dialogue;

                while (win.isOpen())
                {
                    Time dTime = dialogue.getElapsedTime();
                    Event event;
                    while (win.pollEvent(event))
                    {
                        if (event.type == Event::Closed)
                            win.close();
                    }

                    if (dTime.asSeconds() > 3.5)
                    {
                        if (dialogueIndex < dialogues.size() - 1)
                        {
                            dialogueIndex++;
                            dialogue.restart();
                        }
                        else
                            win.close(); // Close the window after the last dialogue
                    }

                    // Update the text to the current dialogue
                    dialogueText.setString(dialogues[dialogueIndex]);

                    // Render
                    win.clear();
                    win.draw(dialogueText);
                    win.display();
                }

                return 0;
            }



            //Draw

            gameplay.clear();


            for (int i = 0; i < 17; i++) {
                for (int j = 0; j < 29; j++)
                {
                    gameplay.draw(maze[i][j]);
                }
            }
            for (int i = 0; i < 17; i++)
            {
                for (int j = 0; j < 29; j++)
                {
                    if (arr[i][j] == 'f')
                    {
                        gameplay.draw(collectible[i][j]);
                    }
                }
            }
            gameplay.draw(timer);
            gameplay.draw(scoreT);
            gameplay.draw(player);
            gameplay.display();

            //Pause game

            if (Keyboard::isKeyPressed(Keyboard::Key::P))
            {
                pauseS.play();

                Clock pauseClock;

                RenderWindow pause(VideoMode(1015, 595), "Paused", Style::Default);
                pause.setFramerateLimit(60);

                pause.setSize(Vector2u(desktopMode.width - 2, desktopMode.height - 35));
                pause.setPosition(Vector2i(-7, -40));

                RectangleShape background(Vector2f(1015.f, 595.f));
                Texture bg;
                bg.loadFromFile("background.jpg");
                background.setTexture(&bg);

                Text paused, resumeT, menu, exit, restart;

                //Paused
                paused.setFont(font);
                paused.setCharacterSize(100);
                paused.setPosition(235.f, 50.f);
                paused.setString("Game Paused");

                //Resume
                resumeT.setFont(font);
                resumeT.setCharacterSize(30);
                resumeT.setPosition(300.f, 200.f);
                resumeT.setString("Press Enter to resume level");

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
                    while (pause.pollEvent(evnt))
                    {
                        if (evnt.type == Event::Closed)
                        {
                            return 0;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
                        {
                            ofstream level3("Level 3.txt");
                            level3 << "1" << endl;
                            level3 << highscore << endl;
                            level3 << score << endl;
                            level3 << player.getPosition().x << endl;
                            level3 << player.getPosition().y << endl;
                            level3 << to_string(time.asSeconds() + prevTime) << endl;
                            for (int i = 0; i < 17; i++)
                            {
                                for (int j = 0; j < 29; j++)
                                {
                                    level3 << arr[i][j];
                                }
                                level3 << endl;
                            }
                            level3.close();
                            gameplay.close();
                            pause.close();
                            return 0;
                        }
                        else if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
                        {
                            // Accumulate pause time and close pause menu
                            pauseTime += pauseClock.getElapsedTime();
                            //pauseClock.restart();
                            pause.close();
                        }
                        else if (Keyboard::isKeyPressed(Keyboard::Key::R))
                        {
                            gameOver = false;
                            lives = 3;
                            spikes = false;
                            player.setPosition(37.5f, 600.f);
                            clock.restart();
                            pause.close();
                            resume = false;
                            score = 0;

                            //Re-initialize collectbles

                            for (int i = 0;i < 17;i++)
                            {
                                for (int j = 0;j < 29;j++)
                                {
                                    if (arr[i][j] == 'z')
                                    {
                                        arr[i][j] = 'f';
                                    }
                                }
                            }

                        }
                        else if (Keyboard::isKeyPressed(Keyboard::Key::M))
                        {
                            ofstream level3("Level 3.txt");
                            level3 << "1" << endl;
                            level3 << highscore << endl;
                            level3 << score << endl;
                            level3 << player.getPosition().x << endl;
                            level3 << player.getPosition().y << endl;
                            level3 << to_string(time.asSeconds() + prevTime) << endl;
                            for (int i = 0; i < 17; i++)
                            {
                                for (int j = 0; j < 29; j++)
                                {
                                    level3 << arr[i][j];
                                }
                                level3 << endl;
                            }
                            level3.close();
                            gameplay.close();
                            pause.close();
                            movetomenu = true;
                        }
                    }

                    pause.clear();
                    pause.draw(background);
                    pause.draw(paused);
                    pause.draw(resumeT);
                    pause.draw(restart);
                    pause.draw(menu);
                    pause.draw(exit);
                    pause.display();
                }
            }
        }
    }

    return 0;
}