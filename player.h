#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include "common.h"
#include <vector>
#include "bullet.h"
#include "stexture.h"


class Player
{
    public:
		//The dimensions of the player
		static const int PLAYER_WIDTH = 30;
		static const int PLAYER_HEIGHT = 30;

		//Maximum axis velocity of the player
		// static const int PLAYER_VEL = 10;
		// static const int PLAYER_ROTATE_SPEED = 3;

        static const float PLAYER_VEL = 200.0f; // Pixels per second
        static const float PLAYER_ROTATE_SPEED = 180.0f; // Degrees per second
        static const Uint32 FIRE_COOLDOWN = 300; // 300ms between shots

		//Initializes the variables
		Player(STexture & mPlayerTexture, STexture & mBulletTexture);

		//Takes key presses and adjusts the player's velocity
		void handleEvent( SDL_Event& e );

		//Moves the player
		void move(float deltaTime);

		//Shows the player on the screen
		void render();

        // Fires a bullet
        void fireBullet();

        // Update and render all bullets
        void updateBullets(float deltaTime);

		float getPosX() const;
        float getPosY() const;
		int getHealth() const;
		void takeDamage(int amount); // New: Player takes damage
        SDL_Rect getBoundingBox() const; // New: Get player's bounding box
		std::vector<Bullet>& getBullets(); // New getter for bullets

    private:
		//The X and Y offsets of the player
		float mPosX, mPosY;

		//The velocity of the player
		float mVelX, mVelY;

		double mRot; // Rotation angle of the player

		double mRotSpeed; // Current speed of rotation

		int health;

		STexture &mPlayerTexture;
        STexture &mBulletTexture;

        // Cooldown timer for firing bullets (prevents firing too many bullets at once)
        Uint32 mLastFireTime;
        // static const Uint32 FIRE_COOLDOWN = 300; // 300ms between shots

        // Vector to store active bullets
        std::vector<Bullet> mBullets;
};
#endif
