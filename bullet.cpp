#include "bullet.h"
#include <cmath>

Bullet::Bullet(int x, int y, double angle, STexture& texture)
    : mPosX(static_cast<float>(x)), mPosY(static_cast<float>(y)), mAngle(angle), gBulletTexture(texture)
{
    double angleRad = angle * M_PI / 180.0;
    // BULLET_SPEED is now pixels per second
    mVelX = BULLET_SPEED * static_cast<float>(cos(angleRad));
    mVelY = BULLET_SPEED * static_cast<float>(sin(angleRad));
    gBulletTexture = texture; // Initialize the bullet texture
}

void Bullet::move(float deltaTime) // Added deltaTime parameter
{
    mPosX += mVelX * deltaTime;
    mPosY += mVelY * deltaTime;
}

void Bullet::render()
{
    gBulletTexture.render(static_cast<int>(mPosX), static_cast<int>(mPosY));
}

bool Bullet::isOffScreen()
{
    return (mPosX < 0 || mPosX > SCREEN_WIDTH || mPosY < 0 || mPosY > SCREEN_HEIGHT);
}
