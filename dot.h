#include <SDL.h>
#include "common.h"

#ifndef STEXTURE_INCLUDED
#define STEXTURE_INCLUDED

#include "stexture.h"

#endif


class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 274;
		static const int DOT_HEIGHT = 61;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 10;

		//Initializes the variables
		Dot(STexture & gDotTexture);

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();

		//Shows the dot on the screen
		void render();

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

		STexture &gDotTexture;
};
