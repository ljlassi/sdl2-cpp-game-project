#include "player.h"

Player::Player(STexture & gPlayerTexture)
    : gPlayerTexture(gPlayerTexture)
{
    //Initialize the offsets
    mPosX = 320; // Center of the screen
    mPosY = 320; // Center of the screen

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    mRot = 0.0; // Initialize rotation angle
    mRotSpeed = 0.0; // Initialize rotation speed

    // No need to set the player texture reference here, already initialized in initializer list
}

void Player::move()
{
    //Move the player left or right
    mPosX += mVelX;
    mRot += mRotSpeed; // Adjust rotation based on horizontal velocity
    //mRot = fmod(mRot, 360.0); // Keep rotation within 0-360 degrees
    if (mRot < 0) {
        mRot += 360.0; // Adjust negative angles to positive
    }
    // If the player is rotating, ensure the rotation angle stays within bounds
    if (mRot >= 360.0) {
        mRot -= 360.0; // Wrap around if it exceeds 360 degrees
    }
    //If the player went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + PLAYER_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the player up or down
    mPosY += mVelY;

    //If the player went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + PLAYER_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }
}

void Player::render()
{
    //Show the player
	gPlayerTexture.render( mPosX, mPosY, nullptr, mRot, nullptr, SDL_FLIP_NONE );

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
            case SDLK_a: mRotSpeed += PLAYER_ROTATE_SPEED;  break;
            case SDLK_d: mRotSpeed -= PLAYER_ROTATE_SPEED;  break;
        }
    }
}