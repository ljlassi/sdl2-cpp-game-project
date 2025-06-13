#ifndef BULLET_H
#define BULLET_H
#include "common.h"
#include "stexture.h"

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

    SDL_Rect getBoundingBox() const; // New: Get bullet's bounding box
    static const int BULLET_DAMAGE = 25; // New: Damage a bullet deals

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