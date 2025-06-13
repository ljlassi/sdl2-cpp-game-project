#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "stexture.cpp"
#include "player.cpp"
#include "bullet.cpp"
#include "common.cpp"
#include "enemy.cpp"


bool initGame();

bool loadGameMedia();

void closeGame();

SDL_Window* gWindow = NULL;

STexture gPlayerTexture;
STexture gBulletTexture;  // Add bullet texture
STexture gEnemyTexture;  // Add enemy texture


bool initGame()
{
	//Init flag
	bool success = true;

	//Init SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		// Use linear texture filtering
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering could not be enabled!" );
		}

		// Create and open window
		gWindow = SDL_CreateWindow( "Shooter Game Prototype", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window cannot be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			// Set Vsync on
			mRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( mRenderer == NULL )
			{
				printf( "Renderer cannot be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize colors for renderer
				SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image wasn't able to initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadGameMedia()
{
	// Whether media loading was successful
	bool success = true;

	// Load player texture
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

	// Load enemy texture
	if( !gEnemyTexture.loadFromFile( "/img/enemy_rectangle.png" ) )
	{
		printf( "Failed to load enemy texture!\n" );
		success = false;
	}

	return success;
}

void closeGame()
{
	//Free the textures
	gPlayerTexture.free();
	gBulletTexture.free();
	gEnemyTexture.free();

	//Destroy the window
	SDL_DestroyRenderer( mRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	mRenderer = NULL;

	// Quit all used SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	// Init SDL and create the window
	if( !initGame() )
	{
		printf( "Something went wrong: Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadGameMedia() )
		{
			printf("Something went wrong: Failed to load media!\n" );
		}
		else
		{	
			// Flag for main loop
			bool quit = false;

			// Handle events
			SDL_Event e;

			// Create player and enemy objects
			// Player uses the player texture and bullet texture
			// Enemy uses the enemy texture
			Player player = Player(gPlayerTexture, gBulletTexture);
			Enemy enemy = Enemy(100, 100, gEnemyTexture); // Create an enemy at position (100, 100)
			enemy.spawn(100, 100); // Spawn the enemy at its initial position

			//Time management for delta time calculation
            Uint32 lastFrameTime = SDL_GetTicks();
            float deltaTime = 0.0f;

			// The game loop itself
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

				// Poll event queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					// Quit event, by user request
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the player
					player.handleEvent( e );
				}

				// Make the player move
				player.move(deltaTime);

				if (enemy.getHealth() > 0) // Only move enemy if it's alive
                {
                    enemy.move(deltaTime, player.getPosX(), player.getPosY());
                }

				if (enemy.getHealth() > 0 && player.getHealth() > 0) {
                    if (checkCollision(player.getBoundingBox(), enemy.getBoundingBox())) {
                        player.takeDamage(enemy.getAttackPower()); // Player takes damage
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


				//Clear the screen
				SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( mRenderer );

				//Render the actual objects
                if (player.getHealth() > 0) { // Only render player if alive
                    player.render();
                } else {
                    printf("Game Over - Player defeated!\n");
                }
				
				// Update and render bullets
				player.updateBullets(deltaTime);

				enemy.render(); // Render the enemy
				// Move the enemy
				enemy.move(deltaTime, player.getPosX(), player.getPosY());

				//Update the screen
				SDL_RenderPresent( mRenderer );

				if (player.getHealth() <= 0) {
                    SDL_Delay(2000); // Wait 2 seconds
                    quit = true;
                }
			}
		}
	}

	//Free the resources and close SDL
	closeGame();

	return 0; 
}
