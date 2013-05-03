#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED

#include "sdlwrap.h"
#include "pointrectcolor.h"

class sdl::Surface
{

private:

//  Variables

    SDL_Surface* surface;

public:

    static Surface screen;

//  Constructors

    Surface(): surface( NULL ) {}

    Surface(SDL_Surface* surf) { surface = surf;}

//  Functions

    void set_pixel(const Point&,const Color&);
    void set_pixel(int,int,const sdl::Color&);

    //void clear_colorkey();

    void load(const char*);
    void load_transparent(const char*);
    void blit(const sdl::Point&,Surface&,const sdl::Rect&);
    void blit(const sdl::Point&,Surface&);

    static SDL_Surface* create_rgb(int,int,Uint8,Uint32,Uint32,Uint32);

    //Color get_colorkey() const;

//  Inline Functions

    SDL_Surface* sdl()                { return surface; }

    void lock()                       { if( SDL_MUSTLOCK(surface) ) if( SDL_LockSurface(surface) == -1 ) throw SDL_GetError(); }

    void unlock()                     { if( SDL_MUSTLOCK(surface) ) SDL_UnlockSurface(surface); }

    void flip()                       { if( SDL_Flip(surface) == -1 ) throw SDL_GetError(); }

    int width() const                 { return surface->w; }

    int height() const                { return surface->h; }

    SDL_PixelFormat* format() const   { return surface->format; }

    void set_colorkey(const sdl::Color& col) { if( SDL_SetColorKey(surface,SDL_SRCCOLORKEY,SDL_MapRGB(surface->format,col.getr(),col.getg(),col.getb())) == -1 )
                                                throw SDL_GetError();
                                             }

    void clear(const Color& col) { if( SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,col.getr(),col.getg(),col.getb())) ) throw SDL_GetError(); }

    void fill(const Rect& r,const Color& c) { SDL_Rect temp = r.sdl();
                                              if( SDL_FillRect( surface , &temp , SDL_MapRGB(surface->format,c.getr(),c.getg(),c.getb()) ) == -1 )
                                                throw SDL_GetError();
                                            }

    void free() { if( surface != NULL ) { SDL_FreeSurface( surface ); surface = NULL; } }


    static SDL_Surface* video_surface() { return SDL_GetVideoSurface(); }

//  Operators

    bool operator!() { return surface == NULL; }

};

#endif // SURFACE_H_INCLUDED
