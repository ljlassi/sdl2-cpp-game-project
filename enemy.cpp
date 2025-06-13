#ifndef ENEMY_INCLUDED
#define ENEMY_INCLUDED
#include "enemy.h"
#endif
#include <cmath>
#include "stexture.h"
#include "common.h"

Enemy::Enemy(int health, int attackPower)
    : health(health), mPosX(0), mPosY(0), mVelX(0), mVelY(0), angle(0)
{
    // Initialize enemy position and velocity
}
void Enemy::takeDamage(int damage)
{
    health -= damage;
    if (health < 0) {
        health = 0; // Prevent negative health
    }
}
int Enemy::getHealth()
{
    return health;
}
void Enemy::move(float deltaTime)
{
    // Update position based on velocity and time
    mPosX += mVelX * deltaTime;
    mPosY += mVelY * deltaTime;

    // Clamp position to screen bounds
    if (mPosX < 0) {
        mPosX = 0;
    } else if (mPosX + ENEMY_WIDTH > SCREEN_WIDTH) {
        mPosX = SCREEN_WIDTH - ENEMY_WIDTH;
    }

    if (mPosY < 0) {
        mPosY = 0;
    } else if (mPosY + ENEMY_HEIGHT > SCREEN_HEIGHT) {
        mPosY = SCREEN_HEIGHT - ENEMY_HEIGHT;
    }
}
void Enemy::spawn(int x, int y)
{
    mPosX = x;
    mPosY = y;
    // Reset velocity
    mVelX = 0;
    mVelY = 0;
// Set initial angle for movement
    angle = 0; // Default angle, can be set to any value based on game logic
// Set velocity based on angle
    mVelX = static_cast<int>(cos(angle * M_PI / 180.0) * 100); // 100 is a speed factor
    mVelY = static_cast<int>(sin(angle * M_PI / 180.0) * 100); // 100 is a speed factor
}
// Render the enemy using its texture
void Enemy::render(STexture& enemyTexture)
{
    enemyTexture.render(mPosX, mPosY);
}
// Getters for position
int Enemy::getPosX()
{
    return mPosX;
}
int Enemy::getPosY()
{
    return mPosY;
}
// Getters for dimensions
int Enemy::getWidth()
{
    return ENEMY_WIDTH;
}
int Enemy::getHeight()
{
    return ENEMY_HEIGHT;
}
// Getters for velocity
int Enemy::getVelX()
{
    return mVelX;
}
int Enemy::getVelY()
{
    return mVelY;
}
// Getters for angle
int Enemy::getAngle()
{
    return angle;
}
int Enemy::getAttackPower()
{
    return attackPower;
}
