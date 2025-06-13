#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "player.cpp"
#include "stexture.cpp"
#define STEXTURE_INCLUDED
#include "bullet.cpp"
#define BULLET_INCLUDED
#ifndef COMMON_INCLUDED
#define COMMON_INCLUDED
#include "common.h"
#endif
#include "stimer.cpp"
#define STIMER_INCLUDED


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
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

	return success;
}

void close()
{
	//Free loaded images
	gPlayerTexture.free();
	gBulletTexture.free();

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

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render objects
				player.render();
				
				// Update and render bullets
				player.updateBullets(deltaTime);

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0; 
}
