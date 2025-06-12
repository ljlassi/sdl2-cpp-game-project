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

    // No need to set the player texture reference here, already initialized in initializer list
}

void Player::move()
{
    //Move the player left or right
    mPosX += mVelX;

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
	gPlayerTexture.render( mPosX, mPosY );
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
        }
    }
}