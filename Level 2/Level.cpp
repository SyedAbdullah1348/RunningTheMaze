#include<sfml\graphics.hpp>
#include<iostream>
#include <sfml/window.hpp>
#include <sfml/audio.hpp>
#include <sfml/system.hpp>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>
using namespace std;
using namespace sf;

int const r = 25;
int const c = 30;
char arr[r][c];
float tilesize = 20;
//-------------------------------------------------------------
//-------------------------------------------------------------
//for fire 
struct Particle {
	CircleShape shape;
	Vector2f velocity;
	float lifetime;
};
struct FireEffect {
	Vector2f position;
	vector<Particle> particles;
	float spawnRate;
	float timeSinceLastSpawn;
	float intervalTimer;
	bool fireActive;

	FireEffect(Vector2f pos, float rate) : position(pos), spawnRate(rate), timeSinceLastSpawn(0), intervalTimer(0), fireActive(true) {}
};
//----------------------------------------------------------
//--------------------------------------------------------

void MazeMaking(RenderWindow& window, RectangleShape& rect, Texture& backtex);
void readdata2D();
bool checkCollisionwithwalls(const FloatRect& playerBounds);

int main() {

	int lives = 2;
	int playerscore = 0;
	const float mov_speed = 0.13f;
	RenderWindow window(VideoMode(c * tilesize, r * tilesize + 30.0f), "Maze Runner Level 2");
	window.setFramerateLimit(60);


	//------------------------------------------------
	//------------------------------------------------
	// fire logic initializations
	// Fire effects at different positions
	vector<FireEffect> fireEffects = {
		FireEffect(Vector2f(19 * tilesize + 1.5f, 2 * tilesize + 10.f), 0.04f),
		FireEffect(Vector2f(11 * tilesize + 1.5f, 11 * tilesize + 10.f), 0.04f),
		FireEffect(Vector2f(23 * tilesize + 1.5f, 21 * tilesize - 20.f), 0.04f),
		FireEffect(Vector2f(9 * tilesize + 1.5f, 19 * tilesize + 10.f), 0.04f)
	};

	// Predefined attributes
	float velocities[][2] = {
		{50.0f, -10.0f}, {60.0f, -5.0f}, {70.0f, 0.0f}, {60.0f, 5.0f}, {50.0f, 10.0f} };
	Color colors[] = { Color::Red, Color::Red, Color::Red };
	const float fireOnDuration = 2.0f;  // Fire active for 2 seconds
	const float fireOffDuration = 2.0f; // No fire for 2 seconds

	// Clock for delta time
	Clock clock;
	//player
	/*CircleShape player;
	player.setRadius(tilesize / 2);
	player.setFillColor(Color::Black);*/
	//CircleShape player(tilesize / 2.4f); // Slightly smaller than a tile
	//player.setFillColor(sf::Color::Red);
	//player.setPosition(0, 0);

	//----------------------------------------------------------
	Texture player;
	player.loadFromFile("Textures/player2.png");
	Sprite playerS;
	playerS.setTexture(player);
	const int frameWidth = 460; // image reso was 1841 * 2400 divided each by 4 as 4 by 4 spritesheet
	const int frameHeight = 600;
	IntRect currentFrame(0, 0, frameWidth, frameHeight); // taking bounds of sprite 
	playerS.setTextureRect(currentFrame);
	playerS.setPosition(0, 0); //player initial position 
	playerS.setScale((float)(3.5 * tilesize) / player.getSize().x, (float)(3.5 * tilesize) / player.getSize().y);// Initial position
	float animationTime = 0.1f;// time for each sprite 
	float elapsedAnimationTime = 0.0f; // max time they can take 
	int Column = 0;
	int Row = 0;


	//---------------------------------------------------------
	RectangleShape box(Vector2f(tilesize, tilesize));
	box.setOutlineColor(Color::Black);
	box.setOutlineThickness(2);
	readdata2D();

	//---------------------------------------------------------
	//background image 
	Texture grass;
	grass.loadFromFile("Textures/blood.jpg");
	Sprite grassb;
	grassb.setTexture(grass);
	grassb.setScale((float)(c * tilesize) / grass.getSize().x, (float)(r * tilesize) / grass.getSize().y);

	//-----------------------------------------------
	Texture net;
	net.loadFromFile("Textures/spider.png");
	vector<Sprite>Spidernet;
	vector<Vector2f>netpos = {
		{22 * tilesize + 10, 1 * tilesize - 9},
		{15 * tilesize, 1 * tilesize},
		{1 * tilesize, 4 * tilesize},
		{16 * tilesize, 15 * tilesize},
		{1 * tilesize, 12 * tilesize},
	};
	for (const auto& position : netpos) {
		Sprite Spidern;
		Spidern.setTexture(net);
		Spidern.setScale((float)(14 * tilesize) / net.getSize().x, (float)(14 * tilesize) / net.getSize().y);
		Spidern.setPosition(position);
		Spidernet.push_back(Spidern);
	}
	//---------------------------------------------------
	//----------------------------------------------------
	// sound of ghosts

	SoundBuffer buffer;
	buffer.loadFromFile("Sound/boo.wav");
	Sound sound;
	sound.setBuffer(buffer);
	bool soundplay = false;

	//sound of fire
	SoundBuffer bufferfire;
	bufferfire.loadFromFile("Sound/fire.mp3");
	Sound soundfire;
	soundfire.setBuffer(bufferfire);
	bool soundplayfire = false;
	//bool soundplay = false;
	//-----------------------------------------------
	//-----------------------------------------------
	Texture skullcoins;
	skullcoins.loadFromFile("Textures/skullcoin2.png");
	vector<Sprite>coins;
	vector<Vector2f>coinpos = {
		{16 * tilesize - 3, 12 * tilesize - 3},
		{6 * tilesize - 3, 6 * tilesize - 3},
		{1 * tilesize - 3, 12 * tilesize - 3},
		{1 * tilesize - 3, 21 * tilesize - 3},
		{9 * tilesize - 3, 14 * tilesize - 3},
		{23 * tilesize - 3, 22 * tilesize - 3},
		{18 * tilesize - 3, 6 * tilesize - 3},
		{9 * tilesize - 3, 23 * tilesize - 3},
		{10 * tilesize - 3, 4 * tilesize - 3},
		{28 * tilesize - 3, 12 * tilesize - 3},
		{25 * tilesize - 3, 6 * tilesize - 3}
	};
	for (const auto& pos : coinpos) {
		Sprite coin;
		coin.setTexture(skullcoins);
		coin.setScale((float)(1.3 * tilesize) / skullcoins.getSize().x, (float)(1.3 * tilesize) / skullcoins.getSize().y);
		coin.setPosition(pos);
		coins.push_back(coin);
	}


	//-------------------------------------------------------
	Texture spookyhands;
	spookyhands.loadFromFile("Textures/hands.png");
	vector<Sprite>hands;
	vector<Vector2f>handpos = {
	{17 * tilesize, 17 * tilesize},
	{3 * tilesize, 9 * tilesize},
	{24 * tilesize, 1 * tilesize}
	};

	for (const auto& pos : handpos) {
		Sprite handsn;
		handsn.setTexture(spookyhands);
		handsn.setScale((float)(3 * tilesize) / spookyhands.getSize().x, (float)(3 * tilesize) / spookyhands.getSize().y);
		handsn.setPosition(pos);
		hands.push_back(handsn);
	}

	//-------------------------------------------
	Texture skull2;
	skull2.loadFromFile("Textures/skull3.png");
	Sprite skull2b;
	skull2b.setTexture(skull2);
	skull2b.setPosition(15 * tilesize, 1 * tilesize);
	skull2b.setScale((float)(4 * tilesize) / skull2.getSize().x, (float)(4 * tilesize) / skull2.getSize().y);

	//-------------------------------------------
	Texture ghost;
	ghost.loadFromFile("Textures/spooky.png");
	Sprite ghostb;
	ghostb.setTexture(ghost);
	ghostb.setPosition(-200, -200);
	ghostb.setScale((float)(6 * tilesize) / ghost.getSize().x, (float)(6 * tilesize) / ghost.getSize().y);

	//text 
	//------------------------------------------
	Font font;
	font.loadFromFile("Fonts/ArialTh.ttf");
	Text text;
	text.setFont(font);
	text.setFillColor(Color::White);
	text.setCharacterSize(14);
	text.setStyle(Text::Bold);
	text.setPosition(20 * tilesize, 25 * tilesize - 1);
	//---------------------------------------
	Text text2;
	text2.setFont(font);
	text2.setFillColor(Color::White);
	text2.setCharacterSize(14);
	text2.setStyle(Text::Bold);
	text2.setPosition(1 * tilesize, 25 * tilesize - 1);

	//-------------------------------------------------
	//---------------------------------------------------
	Clock timer;
	//------------------------------------------------
	//------------------------------------------------
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		//-----------------------------------------------------------
		//------------------------------------------------------------
		//adding time + text and font

		float dt = clock.restart().asSeconds();

		Time elapsed = timer.getElapsedTime();
		float timevalue = round(elapsed.asSeconds() * 100.0f) / 100.0f;
		string stringn = to_string(timevalue);
		text.setString("Time: " + stringn);
		string lives1 = to_string(lives);
		text2.setString("Lives: " + lives1);
		//------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------
		// Update fire effects logic 
		for (auto& fire : fireEffects) {
			fire.timeSinceLastSpawn += dt;
			fire.intervalTimer += dt;

			// Toggle fire on/off based on the interval
			if (fire.fireActive && fire.intervalTimer >= fireOnDuration) {
				fire.fireActive = false; // Turn fire off
				fire.intervalTimer = 0; // Reset the timer
			}
			else if (!fire.fireActive && fire.intervalTimer >= fireOffDuration) {
				fire.fireActive = true; // Turn fire on
				fire.intervalTimer = 0; // Reset the timer
			}

			// Spawn new particles only if fire is active
			if (fire.fireActive && fire.timeSinceLastSpawn >= fire.spawnRate) {
				fire.timeSinceLastSpawn = 0;

				if (fire.particles.size() < 500) { // Limit max particles
					static int velocityIndex = 0, colorIndex = 0;

					// Create a new particle
					Particle p;
					p.shape.setRadius(7.0f); // Fixed size
					p.shape.setFillColor(colors[colorIndex]); // Cycling through predefined colors
					p.shape.setPosition(fire.position); // Spawn at the fire's position
					p.velocity = Vector2f(velocities[velocityIndex][0], velocities[velocityIndex][1]); // Predefined velocities
					p.lifetime = 2.0f; // Fixed lifetime

					// Add the particle to the vector
					fire.particles.push_back(p);

					// Cycle through predefined attributes
					velocityIndex = (velocityIndex + 1) % 5; // Cycle through 5 velocities
					colorIndex = (colorIndex + 1) % 3;       // Cycle through 3 colors
				}
			}
			//----------------------------------------------------------------------------------
			//----------------------------------------------------------------------------------

			//collsion with coins 
			for (auto& skullcoins : coins) {
				if (playerS.getGlobalBounds().intersects(skullcoins.getGlobalBounds())) {
					skullcoins.setPosition(-100, -100);
					playerscore += 100;
				}
			}


			//----------------------------------------------------------------------------------
			//----------------------------------------------------------------------------------

			// Update particles
			for (size_t i = 0; i < fire.particles.size();) {
				Particle& p = fire.particles[i];
				p.lifetime -= dt;

				// Gradually fade color
				Color currentColor = p.shape.getFillColor();

				// This part focuses on fading the color
				if (currentColor.a > 0) {
					float newAlpha = currentColor.a - (255 * dt);
					newAlpha = std::max(0.0f, newAlpha);
					currentColor.a = newAlpha;
				}
				p.shape.setFillColor(currentColor);

				// Move the particle
				p.shape.move(p.velocity * dt);

				// Remove if lifetime is over or fully faded
				if (p.lifetime <= 0 || (currentColor.a == 0)) {
					fire.particles.erase(fire.particles.begin() + i);
				}
				else {
					++i; // Only increment if particle is not removed
				}

				if (playerS.getGlobalBounds().intersects(p.shape.getGlobalBounds())) {
					if (lives == 0) {
						cout << "Game over";
						return 0;
					}
					else {
						lives--;
						playerS.setPosition(0, 0);
					}
				}
			}
		}
		//
		//-------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------
		//movement + collsion + player animation logic 
		bool ani_movement = false;
		Vector2f PlayerCurrentPosition = playerS.getPosition(); // Storing in next location because we need current posiion value later
		Vector2f PLayernextPosition = PlayerCurrentPosition;

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			PLayernextPosition.y -= tilesize * mov_speed; // Move up
			Row = 3; // Assuming the upward animation is in row 3
			ani_movement = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			PLayernextPosition.y += tilesize * mov_speed; // Move down
			Row = 0; // Assuming the upward animation is in row 3
			ani_movement = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			PLayernextPosition.x -= tilesize * mov_speed; // Move left
			Row = 2; // Assuming the upward animation is in row 3
			ani_movement = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			PLayernextPosition.x += tilesize * mov_speed; // Move right
			Row = 1; // Assuming the upward animation is in row 3
			ani_movement = true;
		}
		//updating the position now
	   //------------------------------------------------------------------------------
	   //Checking for screen collision here  

		if (PLayernextPosition.x < 0)
			PLayernextPosition.x = 0;
		else if (PLayernextPosition.x > (c - 1) * tilesize)
			PLayernextPosition.x = (c - 1) * tilesize;
		if (PLayernextPosition.y < 0)
			PLayernextPosition.y = 0;
		else if (PLayernextPosition.y > (r - 1) * tilesize)
			PLayernextPosition.y = (r - 1) * tilesize;

		playerS.setPosition(PLayernextPosition);


		if (checkCollisionwithwalls(playerS.getGlobalBounds())) {
			playerS.setPosition(PlayerCurrentPosition); // if flag came back true then this gives the current position value to set position of player
		}

		//--------------------------------------------------------------------------
		//-------------------------------------------------------------------------
		//---------------------------------------------------------------------------
		// player winning logic
		Vector2f WINLOC;
		WINLOC.x = 29 * tilesize;
		WINLOC.y = 24 * tilesize;
		if (playerS.getPosition() == WINLOC) {
			cout << "You won";
			cout << "Your score is " << playerscore;
			return 0;
		}

		/*if (player.getGlobalBounds().intersects(Coinb.getGlobalBounds())) {
			Coinb.setPosition(-100, -100);
			playerscore += 100;
		}*/

		//---------------------------------------------------------------------------
		//--------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
		// -------------------------------------------------------------------------------
		// Animation logic
		if (ani_movement) {
			elapsedAnimationTime += dt;
			if (elapsedAnimationTime >= animationTime) {
				// Advance to the next frame
				elapsedAnimationTime = 0.0f;
				Column = (Column + 1) % 4; // Loop through columns (4 frames per row)
				currentFrame = sf::IntRect(Column * frameWidth, Row * frameHeight, frameWidth, frameHeight);
				playerS.setTextureRect(currentFrame);
			}
		}
		else {
			// Reset to the first frame of the current row when not moving
			Column = 0;
			currentFrame = sf::IntRect(Column * frameWidth, Row * frameHeight, frameWidth, frameHeight);
			playerS.setTextureRect(currentFrame);
		}

		//-------------------------------------------------------------------------
		//--------------------------------------------------------------------------
		//drawing things 
		window.clear(Color::Black);
		//
		//-------------------------------------------------------------
		//-----------------------------------------------------------
		//all drawings 
		MazeMaking(window, box, grass);


		for (const auto& net : Spidernet) {
			window.draw(net);
		}
		for (const auto& spookyhands : hands) {
			window.draw(spookyhands);
		}
		//soundplayfire = false;
		for (const auto& fire : fireEffects) {
			//soundplayfire = false;
			for (const auto& p : fire.particles) {
				window.draw(p.shape);
			}
			if (soundplayfire == false) {
				soundfire.play();
				soundplayfire = true;
			}
		}
		for (const auto& skullcoins : coins) {
			window.draw(skullcoins);
		}
		//-------------------------------------------------------------
		//-------------------------------------------------------------
		//Ghost reappearence logic
		bool soundplay = false;
		if (playerS.getPosition().x >= 21.0 * tilesize && playerS.getPosition().x <= 22.9 * tilesize && (playerS.getPosition().y >= 23.0 * tilesize && playerS.getPosition().y <= 23.9 * tilesize)) {
			ghostb.setPosition(22 * tilesize, 19 * tilesize);
			window.draw(ghostb);
			if (soundplay == false) {
				sound.play();
				soundplay = true;
			}
			else
				soundplay = false;
		}
		if (playerS.getPosition().x >= 5.0 * tilesize && playerS.getPosition().x <= 6.9 * tilesize && (playerS.getPosition().y >= 7.0 * tilesize && playerS.getPosition().y <= 7.9 * tilesize)) {
			ghostb.setPosition(4 * tilesize, 4 * tilesize);
			window.draw(ghostb);
			if (soundplay == false) {
				sound.play();
				soundplay = true;
			}
			else
				soundplay = false;
		}
		if (playerS.getPosition().x >= 14.0 * tilesize && playerS.getPosition().x <= 15.9 * tilesize && (playerS.getPosition().y >= 17.0 * tilesize && playerS.getPosition().y <= 17.9 * tilesize)) {
			ghostb.setPosition(14 * tilesize, 13 * tilesize);
			window.draw(ghostb);
			if (soundplay == false) {
				sound.play();
				soundplay = true;
			}
			else
				soundplay = false;
		}
		if (playerS.getPosition().x >= 26.0 * tilesize && playerS.getPosition().x <= 26.9 * tilesize && (playerS.getPosition().y >= 4 * tilesize && playerS.getPosition().y <= 4.9 * tilesize)) {
			ghostb.setPosition(25 * tilesize, 2 * tilesize);
			window.draw(ghostb);
			if (soundplay == false) {
				sound.play();
				soundplay = true;
			}
			else
				soundplay = false;
		}
		if (playerS.getPosition().x >= 9.0 * tilesize && playerS.getPosition().x <= 9.9 * tilesize && (playerS.getPosition().y >= 21.0 * tilesize && playerS.getPosition().y <= 21.9 * tilesize)) {
			ghostb.setPosition(9 * tilesize, 18 * tilesize);
			window.draw(ghostb);
			if (soundplay == false) {
				sound.play();
				soundplay = true;
			}
			else
				soundplay = false;
		}
		//-------------------------------------------------------------------------
		//--------------------------------------------------------------------------
		window.draw(text);
		window.draw(skull2b);
		window.draw(text2);
		window.draw(playerS);
		window.display();
	}
}

void readdata2D() {
	ifstream sin;
	sin.open("Maze.txt");
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			sin >> arr[i][j];
		}
	}
}
void MazeMaking(RenderWindow& window, RectangleShape& rect, Texture& backTex) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (arr[i][j] == 'a') {
				rect.setFillColor(Color(105, 105, 105));
				rect.setTexture(nullptr);
			}
			else {
				rect.setTexture(&backTex);
			}
			rect.setPosition(j * tilesize, i * tilesize);
			window.draw(rect);
		}
	}
}
bool checkCollisionwithwalls(const FloatRect& playerBounds) {
	// Iterate through the maze to check if the player collides with any wall
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (arr[i][j] == 'b') { // Only check for wall tiles
				FloatRect wallBounds(j * tilesize, i * tilesize, tilesize, tilesize);
				if (playerBounds.intersects(wallBounds)) {
					return true; // Collision detected
				}
			}
		}
	}
	return false; // No collision
}
