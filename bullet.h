#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>

#ifndef COMMON_INCLUDED
#define COMMON_INCLUDED
#include "common.h"
#endif

#ifndef STEXTURE_INCLUDED
#define STEXTURE_INCLUDED
#include "stexture.h"
#endif

class Bullet {
public:
    // Bullet constants
    static const int BULLET_WIDTH = 10;
    static const int BULLET_HEIGHT = 10;
    static const int BULLET_VEL = 15; // Faster than the player

    // Constructor
    Bullet(int x, int y, double angle, STexture &bulletTexture);

    // Move the bullet
    void move(float deltaTime);

    // Render the bullet
    void render();

    // Check if bullet is out of screen bounds
    bool isOffScreen();

    static const float BULLET_SPEED = 400.0f; // Pixels per second

private:
    float mPosX, mPosY;
    float mVelX, mVelY; // Store as float for precision with deltaTime

    // Angle
    double mAngle;

    // Bullet texture
    // STexture &mBulletTexture;
    STexture& gBulletTexture;
};

#endif
