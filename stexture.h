#ifndef STEXTURE_H
#define STEXTURE_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>

class STexture
{
	public:
		//Initializes variables
		STexture();

		//Deallocates memory
		~STexture();

		//Loads image at specified path
		bool loadFromFile( std::string path, SDL_Renderer* renderer );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

#endif