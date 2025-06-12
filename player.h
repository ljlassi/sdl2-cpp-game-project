#include <SDL.h>
#include "common.h"
#include <vector>
#include "bullet.h"

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
		static const int PLAYER_ROTATE_SPEED = 3;

		//Initializes the variables
		Player(STexture & gPlayerTexture, STexture & gBulletTexture);

		//Takes key presses and adjusts the player's velocity
		void handleEvent( SDL_Event& e );

		//Moves the player
		void move();

		//Shows the player on the screen
		void render();

        // Fires a bullet
        void fireBullet();

        // Update and render all bullets
        void updateBullets();

    private:
		//The X and Y offsets of the player
		int mPosX, mPosY;

		//The velocity of the player
		int mVelX, mVelY;

		double mRot; // Rotation angle of the player

		double mRotSpeed; // Current speed of rotation

		STexture &gPlayerTexture;
        STexture &gBulletTexture;

        // Cooldown timer for firing bullets (prevents firing too many bullets at once)
        Uint32 mLastFireTime;
        static const Uint32 FIRE_COOLDOWN = 300; // 300ms between shots

        // Vector to store active bullets
        std::vector<Bullet> mBullets;
};
