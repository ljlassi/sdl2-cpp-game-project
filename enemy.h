#ifndef ENEMY_H
#define ENEMY_H
#include "stexture.h"
#include "common.h"

class Enemy {
public:
    Enemy(int health, int attackPower);

    void takeDamage(int damage);

    int getHealth();

    static const int ENEMY_WIDTH = 60; // Width of the enemy
    static const int ENEMY_HEIGHT = 25; // Height of the enemy

    // Moves the enemy based on its velocity
    void move(float deltaTime);

    void spawn(int x, int y);

    int getPosX();
    int getPosY();
    void render(STexture& enemyTexture);
    int getAngle(); // Get the current angle of the enemy
    int getVelX();
    int getVelY();
    int getHeight();
    int getWidth();
    int getAttackPower(); // Get the attack power of the enemy

private:
    int health; // Health of the enemy
    //The X and Y offsets of the enemy
    int attackPower; // Attack power of the enemy
    int mPosX, mPosY;

    //The velocity of the enemy
    int mVelX, mVelY;

    int angle; // Movement angle of the enemy

};

#endif