#include <cmath>
#include "enemy.h"

Enemy::Enemy(int health, int attackPower, STexture& enemyTexture)
    : mPosX(0.0f), mPosY(0.0f), mVelX(0.0f), mVelY(0.0f),
      health(health), attackPower(attackPower), mEnemyTexture(enemyTexture)
{

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
void Enemy::move(float deltaTime, float playerX, float playerY)
{
    // Calculate direction vector towards the player
    float dirX = playerX - mPosX;
    float dirY = playerY - mPosY;

    // Calculate distance to player
    // Add a small epsilon to prevent division by zero if distance is extremely small
    float distance = std::sqrt(dirX * dirX + dirY * dirY) + 0.0001f;

    // Normalize the direction vector
    float normX = dirX / distance;
    float normY = dirY / distance;

    // Set velocity towards the player
    mVelX = normX * ENEMY_SPEED;
    mVelY = normY * ENEMY_SPEED;

    // Update position based on velocity and time
    mPosX += mVelX * deltaTime;
    mPosY += mVelY * deltaTime;

    // Clamp position to screen bounds (optional, or handle collision differently)
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
    mPosX = static_cast<float>(x);
    mPosY = static_cast<float>(y);
    // Reset velocity; 'move' will calculate it based on player position
    mVelX = 0.0f;
    mVelY = 0.0f;
    health= 100; // Reset health to initial value
}

SDL_Rect Enemy::getBoundingBox() const
{
    return {static_cast<int>(mPosX), static_cast<int>(mPosY), ENEMY_WIDTH, ENEMY_HEIGHT};
}



// Render the enemy using its texture
void Enemy::render()
{
    this->mEnemyTexture.render(static_cast<int>(mPosX), static_cast<int>(mPosY));
}
// Getters for position
float Enemy::getPosX() const
{
    return mPosX;
}
float Enemy::getPosY() const
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
int Enemy::getAttackPower()
{
    return attackPower;
}
