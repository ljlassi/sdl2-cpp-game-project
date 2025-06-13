#ifndef ENEMY_H
#define ENEMY_H
#include "stexture.h"
#include "common.h"

class Enemy {
public:
    Enemy(int health, int attackPower, STexture& enemyTexture);

    void takeDamage(int damage);

    int getHealth();

    static const int ENEMY_WIDTH = 60; // Width of the enemy
    static const int ENEMY_HEIGHT = 25; // Height of the enemy
    static const float ENEMY_SPEED = 75.0f;

    // Moves the enemy based on its velocity
    void move(float deltaTime, float playerX, float playerY);

    void spawn(int x, int y);

    float getPosX() const;
    float getPosY() const;
    void render();
    int getAngle(); // Get the current angle of the enemy
    int getVelX();
    int getVelY();
    int getHeight();
    int getWidth();
    int getAttackPower(); // Get the attack power of the enemy
    SDL_Rect getBoundingBox() const; // New: Get enemy's bounding box

private:
    int health; // Health of the enemy
    //The X and Y offsets of the enemy
    int attackPower; // Attack power of the enemy
    float mPosX, mPosY;

    //The velocity of the enemy
    float mVelX, mVelY;

    STexture& mgEnemyTexture; // Reference to the enemy texture

};

#endif