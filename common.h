#ifndef COMMON_H
#define COMMON_H
#include <SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
class Common {
public:
    inline bool checkCollision(SDL_Rect a, SDL_Rect b);
};

#endif
