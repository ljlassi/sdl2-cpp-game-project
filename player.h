#include <SDL.h>
#include "common.h"

#ifndef STEXTURE_INCLUDED
#define STEXTURE_INCLUDED

#include "stexture.h"

#endif


class Player
{
    public:
		//The dimensions of the player
		static const int PLAYER_WIDTH = 30;
		static const int PLAYER_HEIGHT = 30;

		//Maximum axis velocity of the player
		static const int PLAYER_VEL = 10;
		static const int PLAYER_ROTATE_SPEED = 10;

		//Initializes the variables
		Player(STexture & gPlayerTexture);

		//Takes key presses and adjusts the player's velocity
		void handleEvent( SDL_Event& e );

		//Moves the player
		void move();

		//Shows the player on the screen
		void render();

    private:
		//The X and Y offsets of the player
		int mPosX, mPosY;

		//The velocity of the player
		int mVelX, mVelY;

		STexture &gPlayerTexture;
};
