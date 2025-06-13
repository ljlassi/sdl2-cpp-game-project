#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "stexture.cpp"
#include "player.cpp"
#include "bullet.cpp"
#include "common.cpp"
#include "stimer.cpp"
#include "enemy.cpp"


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

STexture gPlayerTexture;
STexture gBulletTexture;  // Add bullet texture
STexture gEnemyTexture;  // Add enemy texture


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Shooter Game Prototype", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load player texture
	if( !gPlayerTexture.loadFromFile( "/img/player.png" ) )
	{
		printf( "Failed to load player texture!\n" );
		success = false;
	}

	//Load bullet texture
	if( !gBulletTexture.loadFromFile( "/img/shot.png" ) )
	{
		printf( "Failed to load bullet texture!\n" );
		success = false;
	}

	if( !gEnemyTexture.loadFromFile( "/img/enemy_rectangle.png" ) )
	{
		printf( "Failed to load enemy texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gPlayerTexture.free();
	gBulletTexture.free();
	gEnemyTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The player that will be moving around on the screen
			Player player = Player(gPlayerTexture, gBulletTexture);

			Enemy enemy = Enemy(100, 100, gEnemyTexture); // Create an enemy at position (100, 100)
			enemy.spawn(100, 100); // Spawn the enemy at its initial position

			//Time management for delta time calculation
            Uint32 lastFrameTime = SDL_GetTicks();
            float deltaTime = 0.0f;

			//While application is running
			while( !quit )
			{

				//Calculate delta time
                Uint32 currentFrameTime = SDL_GetTicks();
                deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f; // Convert milliseconds to seconds
                lastFrameTime = currentFrameTime;

                // Cap delta time to avoid unusually large jumps if debugging or system lags
                if (deltaTime > 0.1f) { // e.g., max 0.1 seconds per frame
                    deltaTime = 0.1f;
                }

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the player
					player.handleEvent( e );
				}

				//Move the player
				player.move(deltaTime);

				if (enemy.getHealth() > 0) // Only move enemy if it's alive
                {
                    enemy.move(deltaTime, player.getPosX(), player.getPosY());
                }

				if (enemy.getHealth() > 0 && player.getHealth() > 0) {
                    if (checkCollision(player.getBoundingBox(), enemy.getBoundingBox())) {
                        player.takeDamage(enemy.getAttackPower()); // Player takes damage
                        // Optional: Add a small knockback or temporary invincibility for player
                        // Optional: Enemy could also take some minor damage or be knocked back
                        printf("Player hit by enemy! Player health: %d\n", player.getHealth());
                    }
                }

                // Bullets vs Enemy
                if (enemy.getHealth() > 0) {
                    std::vector<Bullet>& bullets = player.getBullets(); // Need a getter for mBullets
                    for (size_t i = 0; i < bullets.size(); ++i) {
                        if (checkCollision(bullets[i].getBoundingBox(), enemy.getBoundingBox())) {
                            enemy.takeDamage(Bullet::BULLET_DAMAGE);
                            printf("Enemy hit by bullet! Enemy health: %d\n", enemy.getHealth());
                            bullets.erase(bullets.begin() + i); // Remove bullet
                            i--; // Adjust index after removal

                            if (enemy.getHealth() <= 0) {
                                printf("Enemy defeated!\n");
                                // Optional: Handle enemy death (e.g., remove from a list of enemies, play sound)
								enemy.spawn(-100, -100); // Move enemy off-screen or reset position
                                break; // Stop checking bullets for this enemy if it's dead
                            }
                        }
                    }
                }
                
                // --- End Collision Detection ---


				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render objects
                if (player.getHealth() > 0) { // Only render player if alive
                    player.render();
                } else {
                    // Optional: Display game over message
                    printf("Game Over - Player defeated!\n");
                    // quit = true; // Or handle game over state differently
                }
				
				// Update and render bullets
				player.updateBullets(deltaTime);

				enemy.render(); // Render the enemy
				// Move the enemy
				enemy.move(deltaTime, player.getPosX(), player.getPosY());

				//Update screen
				SDL_RenderPresent( gRenderer );

				if (player.getHealth() <= 0) {
                     // Optional: Add a delay or specific game over screen before quitting
                    SDL_Delay(2000); // Wait 2 seconds
                    quit = true;
                }
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0; 
}
