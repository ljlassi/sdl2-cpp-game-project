#include <iostream>
#include "SDL/include/SDL.h"

// You shouldn't really use this statement, but it's fine for small programs

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args) {

    // Pointers to our window and surface
    SDL_Surface* winSurface = NULL;
    SDL_Window* window = NULL;

    // Initialize SDL. SDL_Init will return -1 if it fails.
    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        getchar();
        // End the program
        return 1;
    } 

    // Create our window
    window = SDL_CreateWindow( "Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN );

    // Make sure creating the window succeeded
    if ( !window ) {
        std::cout << "Error creating window: " << SDL_GetError()  << std::endl;
        getchar();
        // End the program
        return 1;
    }

    // Get the surface from the window
    winSurface = SDL_GetWindowSurface( window );

    // Make sure getting the surface succeeded
    if ( !winSurface ) {
        std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
        getchar();
        // End the program
        return 1;
    }

    // Fill the window with a white rectangle
    SDL_FillRect( winSurface, NULL, SDL_MapRGB( winSurface->format, 255, 255, 255 ) );

    // Update the window display
    SDL_UpdateWindowSurface( window );

    while(true)
    {
    SDL_Event e;
        while (SDL_PollEvent(&e)) 
        {
            if(e.type == SDL_QUIT)
            {
                    SDL_DestroyWindow( window );

                // Quit SDL
                SDL_Quit();
                
                // End the program
                return 0;
                break;
            }
            // Handle events
        }

        // "Frame" logic     
    }


    // Put the code that is executed every "frame". 
    // Under "frame" I mean any logic that is run every time there is no app events to process       

    // Destroy the window. This will also destroy the surface
    SDL_DestroyWindow( window );

    // Quit SDL
    SDL_Quit();
    
    // End the program
    return 0;
}

