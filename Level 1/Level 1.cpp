//#include <SFML/graphics.hpp>
//#include <SFML/window.hpp>
//#include <SFML/system.hpp>
//#include <iostream>
//#include <fstream>
//#include <SFML/Audio.hpp>
//using namespace std;
//using namespace sf;
//
//int main()
//{
//    RenderWindow gameplay(VideoMode(680, 680), "the maze runner : metamorphosis", Style::Default);
//    char arr[17][17];
//    char collectibles[17][17];
//    RectangleShape mazecollect[17][17];
//    RectangleShape maze[17][17];
//    RectangleShape wall(Vector2f(40.f, 40.f)), floor(Vector2f(40.f, 40.f)), end(Vector2f(40.f, 40.f)), puddle(Vector2f(40.f, 40.f)), go(Vector2f(40.f, 40.f)), coin(Vector2f(30.f, 30.f));
//    //Texts
//    Text text;
//    Font font;
//    //Blocks
//    Texture start;
//    Texture collect;
//    Texture water;
//    Texture brick;
//    Texture grass;
//    Texture win;
//    Texture player;
//    //Load
//    if (!player.loadFromFile("player.png"))
//        cout << "Couldn't load from file" << endl;
//    if (!collect.loadFromFile("collect1.png"))
//        cout << "Couldn't load from file" << endl;
//    if (!start.loadFromFile("start.png"))
//        cout << "Couldn't load from file" << endl;
//    go.setTexture(&start);
//    if (!water.loadFromFile("hurdle.jpg"))
//        cout << "Couldn't load from file" << endl;
//    puddle.setTexture(&water);
//    if (!win.loadFromFile("endflag1.png"))
//        cout << "Couldn't load from file" << endl;
//    end.setTexture(&win);
//    if (!brick.loadFromFile("wall2.jpg"))
//        cout << "Couldn't load from file" << endl;
//    if (!grass.loadFromFile("grass2.jpg"))
//        cout << "Couldn't load from file" << endl;
//    if (!font.loadFromFile("font.ttf"));
//    cout << "Couldn't load from file" << endl;
//    //settexture
//    text.setFont(font);
//    text.setCharacterSize(20);
//    text.setFillColor(sf::Color::White);
//    text.setPosition(10.f, 10.f);
//    wall.setTexture(&brick);
//    floor.setTexture(&grass);
//    coin.setTexture(&collect);
//    gameplay.setFramerateLimit(60);
//
//    Sprite pl;
//    pl.setTexture(player);
//    pl.setTextureRect(IntRect(0, 306.5, 107.5, 153.25));
//    pl.setScale(Vector2f(0.3f, 0.15f));
//    pl.setPosition(55, 540);
//    // Maze
//    string line;
//    ifstream file;
//    file.open("youwon.txt");
//    for (int i = 0; i < 17; i++)
//    {
//        for (int j = 0; j < 17; j++)
//        {
//            file >> arr[i][j];
//            cout << arr[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << "Collectibles" << endl;
//    //COLLECTIBLES
//    string line1;
//    ifstream filecollect;
//    filecollect.open("maze.txt");
//    for (int i = 0; i < 17; i++)
//    {
//        for (int j = 0; j < 17; j++)
//        {
//            filecollect >> collectibles[i][j];
//            cout << collectibles[i][j] << " ";
//        }
//        cout << endl;
//    }
//    // Sounds
//    SoundBuffer pickup;
//    pickup.loadFromFile("coinsound.wav");
//    Sound pick;
//    pick.setBuffer(pickup);
//    SoundBuffer jumpsound;
//    jumpsound.loadFromFile("jumpsound.wav");
//    Sound jumpS;
//    jumpS.setBuffer(jumpsound);
//    //Music
//    Music Music;
//    if (!Music.openFromFile("music.wav"))
//        cout << "Couldn't load from file" << endl;
//    Music.setLoop(true);
//    Music.setVolume(50.f);
//    Music.play();
//
//
//
//    // load the maze
//    for (int i = 0; i < 17; i++)
//    {
//        for (int j = 0; j < 17; j++)
//        {
//            if (arr[i][j] == 'w')
//            {
//                maze[i][j] = wall;
//                maze[i][j].setPosition(j * 40, i * 40);
//            }
//            else if (arr[i][j] == 'f')
//            {
//                maze[i][j] = floor;
//                maze[i][j].setPosition(j * 40, i * 40);
//            }
//            else if (arr[i][j] == 'W')
//            {
//                maze[i][j] = end;
//                maze[i][j].setPosition(j * 40, i * 40);
//            }
//            else if (arr[i][j] == 'p')
//            {
//                maze[i][j] = puddle;
//                maze[i][j].setPosition(j * 40, i * 40);
//            }
//            else if (arr[i][j] == 'g')
//            {
//                maze[i][j] = go;
//                maze[i][j].setPosition(j * 40, i * 40);
//            }
//        }
//    }
//    for (int i = 0; i < 17; i++)
//    {
//        for (int j = 0; j < 17; j++)
//        {
//            if (collectibles[i][j] == 'c')
//            {
//                mazecollect[i][j] = coin;
//                mazecollect[i][j].setPosition(j * 40, i * 40);
//            }
//        }
//    }
//    int score = 0;
//    text.setString("Current Score : " + to_string(score));
//    //Main loop
//    while (gameplay.isOpen())
//    {
//        bool left = true, right = true, up = true, down = true;
//        bool cleft = true, cright = true, cup = true, cdown = true;
//        Event evnt;
//        while (gameplay.pollEvent(evnt))
//        {
//            if (evnt.type == Event::Closed)
//            {
//                gameplay.close();
//                return 0;
//            }
//            if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
//                gameplay.close();
//        }
//        //Collision
//        float playerleft = pl.getPosition().x;
//        float playerright = playerleft + 25.f;
//        float playertop = pl.getPosition().y;
//        float playerbottom = playertop + 25.f;
//        for (int i = 0; i < 17; i++)
//        {
//
//            for (int j = 0; j < 17; j++)
//            {
//
//                if (arr[i][j] == 'w')
//                {
//                    float wallleft = maze[i][j].getPosition().x;
//                    float wallright = wallleft + 40.f;
//                    float walltop = maze[i][j].getPosition().y;
//                    float wallbottom = walltop + 40.f;
//
//                    if (playerright > wallleft && playerleft < wallright && playertop < wallbottom && playerbottom > walltop)
//                    {
//
//                        if ((playerright > wallleft && playerleft < wallleft) || playerright >= 680)
//                        {
//                            right = false;
//                        }
//                        if ((playerleft < wallright && playerright > wallright) || playerleft <= 0)
//                        {
//                            left = false;
//                        }
//
//
//                        if (playerbottom > walltop && playertop < walltop)
//                        {
//                            down = false;
//                        }
//                        if (playertop < wallbottom && playerbottom > wallbottom)
//                        {
//                            up = false;
//                        }
//                    }
//                }
//
//                //Jump
//                int jump = false;
//                if (Keyboard::isKeyPressed(Keyboard::Space))
//                {
//                    jump = true;
//
//                }
//                if (arr[i][j] == 'p')
//                {
//                    float hurdleleft = maze[i][j].getPosition().x;
//                    float hurdleright = hurdleleft + 40.f;
//                    float hurdletop = maze[i][j].getPosition().y;
//                    float hurdlebottom = hurdletop + 40.f;
//
//
//                    if (arr[i][j] == 'p' && jump == true)
//                    {
//                        jumpS.play();
//                    }
//
//                    if ((playerright > hurdleleft && playerleft < hurdleright && playertop < hurdlebottom && playerbottom > hurdletop) && jump == false)
//                    {
//                        int count = 0;
//
//                        if (playerright > hurdleleft && playerleft < hurdleleft)
//                        {
//                            right = false;
//                        }
//                        if (playerleft < hurdleright && playerright > hurdleright)
//                        {
//                            left = false;
//                        }
//                        if (playerbottom > hurdletop && playertop < hurdletop)
//                        {
//
//                            down = false;
//                        }
//                        if (playertop < hurdlebottom && playerbottom > hurdlebottom)
//                        {
//
//                            up = false;
//                        }
//                    }
//
//                }
//
//                if (pl.getPosition().x + 20 >= 660 && pl.getPosition().y + 20 >= 140)
//                {
//                    gameplay.close();
//                }
//                if (pl.getPosition().x <= 0)
//                {
//                    left = false;
//                }
//            }
//        }
//
//        //COLLECTIBLES COLLISION AND SCORE
//        for (int i = 0; i < 17; i++)
//        {
//            score = 0;
//            for (int j = 0; j < 17; j++)
//            {
//                if (pl.getGlobalBounds().intersects(coin.getGlobalBounds()))
//                {
//                    mazecollect[i][j].setPosition(Vector2f(-200.f, -200.f));
//                    score += 50;
//
//                }
//                
//            }
//            text.setString("Current Score : " + to_string(score));
//        }
//
//        //MOVEMENTS
//
//        if (right && (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right)))
//        {
//            int xtexture = 0;
//            xtexture = int(pl.getPosition().x / 10) % 4;
//            xtexture = xtexture * 107.5;
//            pl.setTextureRect(IntRect(xtexture, 306.5, 107.5, 153.25));
//            pl.move(3.f, 0.f);
//        }
//
//        if (left && (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left)))
//        {
//            int xtexture = 0;
//            xtexture = int(pl.getPosition().x / 10) % 4;
//            xtexture = xtexture * 107.5;
//            pl.setTextureRect(IntRect(xtexture, 153.25, 107.5, 153.25));
//            pl.move(-3.f, 0.f);
//        }
//        if (up && (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up)))
//        {
//            int ytexture = 0;
//            ytexture = int(pl.getPosition().y / 10) % 4;
//            ytexture = ytexture * 107.5;
//            pl.setTextureRect(IntRect(ytexture, 459.75, 107.5, 153.25));
//            pl.move(0.f, -3.f);
//        }
//        if (down && (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down)))
//        {
//            int ytexture = 0;
//            ytexture = int(pl.getPosition().y / 10) % 4;
//            ytexture = ytexture * 107.5;
//            pl.setTextureRect(IntRect(ytexture, 0, 107.5, 153.25));
//            pl.move(0.f, 3.f);
//        }
//
//        gameplay.clear();
//        // Draw maze
//        for (int i = 0; i < 17; i++)
//        {
//            for (int j = 0; j < 17; j++)
//            {
//                gameplay.draw(maze[i][j]);
//            }
//        }
//        for (int i = 0; i < 17; i++)
//        {
//            for (int j = 0; j < 17; j++)
//            {
//                gameplay.draw(mazecollect[i][j]);
//            }
//        }
//        gameplay.draw(pl);
//        gameplay.draw(text);
//        gameplay.display();
//    }
//}
//
