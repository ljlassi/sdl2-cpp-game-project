#include "player.h"
#include <cmath>

Player::Player(STexture & mPlayerTexture, STexture & mBulletTexture)
    : mPlayerTexture(mPlayerTexture), mBulletTexture(mBulletTexture)
{
    //Initialize the offsets
    // mPosX = 320; // Center of the screen
    // mPosY = 320; // Center of the screen

    mPosX = SCREEN_WIDTH / 2.0f; 
    mPosY = SCREEN_HEIGHT / 2.0f;

    //Initialize the velocity
    mVelX = 0.0;
    mVelY = 0.0;

    mRot = 0.0; // Initialize rotation angle
    mRotSpeed = 0.0; // Initialize rotation speed

    mLastFireTime = 0;

    mBulletTexture = mBulletTexture; // Initialize bullet texture

    // Initialize health
    health = 100; // Set initial health
}

float Player::getPosX() const
{
    return mPosX;
}

float Player::getPosY() const
{
    return mPosY;
}

int Player::getHealth() const
{
    return health;
}

void Player::takeDamage(int amount)
{
    health -= amount;
    if (health < 0)
    {
        health = 0;
    }
    // Potentially add game over logic here or in main loop if health is 0
}

SDL_Rect Player::getBoundingBox() const
{
    return {static_cast<int>(mPosX), static_cast<int>(mPosY), PLAYER_WIDTH, PLAYER_HEIGHT};
}

void Player::move(float deltaTime) // Added deltaTime parameter
{
    //Update rotation based on rotation speed and time
    mRot += mRotSpeed * deltaTime; 

    // Normalize rotation angle
    if (mRot < 0.0) {
        mRot += 360.0; 
    } else if (mRot >= 360.0) {
        mRot -= 360.0; 
    }

    //Move the player left or right based on velocity and time
    mPosX += mVelX * deltaTime;

    //If the player went too far to the left or right, clamp position
    if( mPosX < 0 )
    {
        mPosX = 0;
    }
    else if( mPosX + PLAYER_WIDTH > SCREEN_WIDTH )
    {
        mPosX = SCREEN_WIDTH - PLAYER_WIDTH;
    }

    //Move the player up or down based on velocity and time
    mPosY += mVelY * deltaTime;

    //If the player went too far up or down, clamp position
    if( mPosY < 0 )
    {
        mPosY = 0;
    }
    else if( mPosY + PLAYER_HEIGHT > SCREEN_HEIGHT )
    {
        mPosY = SCREEN_HEIGHT - PLAYER_HEIGHT;
    }
}

void Player::render()
{
    //Show the player
	mPlayerTexture.render( mPosX, mPosY, nullptr, mRot, nullptr, SDL_FLIP_NONE );

    // Optionally, you can render a rectangle around the player for debugging
    // SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    // SDL_Rect rect = { mPosX, mPosY, PLAYER_WIDTH, PLAYER_HEIGHT };
    // SDL_RenderDrawRect(gRenderer, &rect);
}

void Player::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= PLAYER_VEL; break;
            case SDLK_DOWN: mVelY += PLAYER_VEL; break;
            case SDLK_LEFT: mVelX -= PLAYER_VEL; break;
            case SDLK_RIGHT: mVelX += PLAYER_VEL; break;
            case SDLK_a: mRot -= PLAYER_ROTATE_SPEED;  break;
            case SDLK_d: mRot += PLAYER_ROTATE_SPEED;  break;
            case SDLK_SPACE: fireBullet(); break; // Fire bullet on space press
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += PLAYER_VEL; break;
            case SDLK_DOWN: mVelY -= PLAYER_VEL; break;
            case SDLK_LEFT: mVelX += PLAYER_VEL; break;
            case SDLK_RIGHT: mVelX -= PLAYER_VEL; break;
            // Reset mRotSpeed if the corresponding key is released
            case SDLK_a: if( mRotSpeed < 0.0f ) mRotSpeed = 0.0f; else mRotSpeed += PLAYER_ROTATE_SPEED; break;
            case SDLK_d: if( mRotSpeed > 0.0f ) mRotSpeed = 0.0f; else mRotSpeed -= PLAYER_ROTATE_SPEED; break;
        }
    }
}

void Player::fireBullet()
{
    // Check cooldown to prevent firing too rapidly
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - mLastFireTime > FIRE_COOLDOWN)
    {
        // Calculate bullet spawn position (center of the player)
        int bulletX = mPosX + PLAYER_WIDTH / 2;
        int bulletY = mPosY + PLAYER_HEIGHT / 2;

        // Create a new bullet and add it to the vector using push_back instead of emplace_back
        Bullet newBullet(bulletX, bulletY, mRot, mBulletTexture);
        mBullets.push_back(newBullet);
        
        // Update last fire time
        mLastFireTime = currentTime;
    }
}

void Player::updateBullets(float deltaTime) // Added deltaTime parameter
{
    // Move all bullets and remove those that go off-screen
    for (int i = 0; i < mBullets.size(); i++) // Use size_t for loop counter with mBullets.size()
    {
        mBullets[i].move(deltaTime); // Pass deltaTime to bullet's move method
        
        // If bullet is off-screen, remove it from the vector
        if (mBullets[i].isOffScreen())
        {
            mBullets.erase(mBullets.begin() + i);
            i--; // Adjust index after erasing
        }
        else
        {
            mBullets[i].render();
        }
    }
}

std::vector<Bullet>& Player::getBullets()
{
    return mBullets;
}
