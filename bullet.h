#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>
#include "common.h"

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
    void move();

    // Render the bullet
    void render();

    // Check if bullet is out of screen bounds
    bool isOffScreen();

private:
    // Position
    int mPosX, mPosY;
    
    // Velocity components based on angle
    double mVelX, mVelY;

    // Angle
    double mAngle;

    // Bullet texture
    STexture &mBulletTexture;
};

#endif