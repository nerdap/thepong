#include "surface.h"

using sdl::Surface;

Surface Surface::screen;

/*

Description : Loads an image from a file onto a surface, and optimizes it
              using SDL_DisplayFormat(). Should be called after calling set_video()
              Can load several formats such as JPG,PNG,BMP and more.
              Use this function when you need to load an image with a color
              to be made transparent.

*/

void Surface::load(const char* filename)
{
    SDL_Surface* image = IMG_Load( filename );

    if( image == NULL )
        throw IMG_GetError();

    SDL_Surface* optimized_image = SDL_DisplayFormat( image );

    SDL_FreeSurface( image );

    surface = optimized_image;
}

/*
Description : Same as Surface::load() but uses SDL_DisplayFormatAlpha() instead
              of SDL_DisplayFormat(). Use this on images which already have the
              required transparency.

*/

void Surface::load_transparent(const char* filename)
{
    SDL_Surface* image = IMG_Load( filename );

    if( image == NULL )
        throw IMG_GetError();

    SDL_Surface* optimized_image = SDL_DisplayFormatAlpha( image );

    SDL_FreeSurface( image );

    surface = optimized_image;
}

/*
Description : Wraps SDL_BlitSurface().

Parameters : pt is an sdl::Point to where the image is going to be drawn
             with respect to the destination surface. src is the source
             surface and pclip is the clipping rectangle.

Usage      : destination.blit( point_to_blit_to , source , clipping_rectangle );

*/

void Surface::blit(const sdl::Point& pt,sdl::Surface& src,const sdl::Rect& pclip)
{
    SDL_Rect offset;
    SDL_Rect clip_rect = pclip.sdl();       //  you get a warning if you directly use pclip.sdl();

    offset.x = pt.getx();
    offset.y = pt.gety();

    if( SDL_BlitSurface( src.sdl() , &clip_rect , surface , &offset ) == -1 )
        throw SDL_GetError();
}

/*
Description : An overload for Surface::blit(). Here the clipping rectangle is set to NULL.

*/

void Surface::blit(const sdl::Point& pt,sdl::Surface& src)
{
    SDL_Rect offset;

    offset.x = pt.getx();
    offset.y = pt.gety();

    if( SDL_BlitSurface( src.sdl() , NULL , surface , &offset ) == -1 )
        throw SDL_GetError();
}

/*
Description : Calls Surface::set_pixel(x,y,col).

*/

void Surface::set_pixel(const sdl::Point& pt,const Color& col)
{
    set_pixel( pt.getx() , pt.gety() , col );
}

/*
Description : This is fairly hard to explain so just assume that it works :P

Parameters  : x-y coordinates and the color of the pixel.

*/

void Surface::set_pixel(int x,int y,const Color& col)
{
    if( (x > surface->w) || (y > surface->h) || (x < 0) || (y < 0) )
        return;

    Uint32 color = SDL_MapRGB( surface->format , col.getr() , col.getg() , col.getb() );

    switch( surface->format->BytesPerPixel)
    {
        case 1:
        {
            Uint8* bufp = NULL;
            bufp = (Uint8*)surface->pixels + (y * surface->pitch) + x;
            *bufp = color;
            break;
        }

        case 2:
        {
            Uint16* bufp = NULL;
            bufp = (Uint16*)surface->pixels + (y * surface->pitch)/2 + x;
            *bufp = color;
            break;
        }

        case 3:
        {
            Uint8* bufp = NULL;
            bufp = (Uint8*)surface->pixels + (y * surface->pitch) * 3 + x;
            if( SDL_BYTEORDER == SDL_LIL_ENDIAN )
            {
                bufp[0] = color;
                bufp[1] = color >> 8;
                bufp[2] = color >> 16;
            }

            else
            {
                bufp[2] = color;
                bufp[1] = color >> 8;
                bufp[0] = color >> 16;
            }
            break;
        }

        case 4:
        {
            Uint32* bufp = NULL;
            bufp = (Uint32*)surface->pixels + (y * surface->pitch)/4 + x;
            *bufp = color;
            break;
        }

        default: break;
    }
}

/*
Description : Creates an empty surface. We probably won't use this one,
              so it can be safely ignored for now.
*/

SDL_Surface* sdl::Surface::create_rgb(int w,int h,Uint8 bpp,Uint32 rmask,Uint32 gmask,Uint32 bmask)
{

    SDL_Surface* temp = SDL_CreateRGBSurface( SDL_HWSURFACE | SDL_SRCCOLORKEY , w , h , bpp , rmask , gmask , bmask , 0 );

    if( temp == NULL )
        throw SDL_GetError();

    return temp;

}
