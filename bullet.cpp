#include "bullet.h"
#include <cmath>

Bullet::Bullet(int x, int y, double angle, STexture &bulletTexture)
    : mPosX(x), mPosY(y), mAngle(angle), mBulletTexture(bulletTexture)
{
    // Calculate velocity components based on angle
    // Convert angle from degrees to radians
    double radians = (90 - angle) * M_PI / 180.0; // Adjust for SDL's coordinate system
    
    mVelX = BULLET_VEL * cos(radians);
    mVelY = -BULLET_VEL * sin(radians); // Negative because SDL Y increases downward
}

void Bullet::move()
{
    // Move based on velocity components
    mPosX += mVelX;
    mPosY += mVelY;
}

void Bullet::render()
{
    // Render the bullet with its angle
    mBulletTexture.render(mPosX - BULLET_WIDTH/2, mPosY - BULLET_HEIGHT/2, nullptr, mAngle, nullptr, SDL_FLIP_NONE);
}

bool Bullet::isOffScreen()
{
    return (mPosX < -BULLET_WIDTH || mPosX > SCREEN_WIDTH || 
            mPosY < -BULLET_HEIGHT || mPosY > SCREEN_HEIGHT);
}
