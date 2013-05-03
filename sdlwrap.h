#ifndef SDLWRAP_H_INCLUDED
#define SDLWRAP_H_INCLUDED

/*

Contains the (forward) declarations
of the wrapper classes, functions and
typedefs. The actual definitions of the
classes are in other header files which
will not be included here.

*/


//  Includes

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cmath>

#ifndef NULL
    #define NULL 0
#endif

namespace sdl
{

//      Wrapper Classes

    class Surface;
    class Color;
    class Point;
    class Rect;
    class Event;
    class Text;

    class SoundManager;

//      Typedefs

    typedef SDL_PixelFormat PixelFormat;
    typedef SDL_VideoInfo   VideoInfo;
    typedef SDL_Palette     Palette;
    typedef SDL_Overlay     Overlay;
    typedef TTF_Font        Font;

//      Functions

    SDL_Surface* set_video(Uint16,Uint16,Uint8,Uint32);

    void draw_line(const Point&,const Point&,const Color&,Surface&);

    bool check_collision(const Rect&,const Rect&);



//      Inline functions

    inline void quitsdl()               { SDL_Quit(); }

    inline void init(Uint32 flags)      { if( SDL_Init( flags ) == -1 ) throw SDL_GetError(); }

    inline void open_audio()            { if( Mix_OpenAudio( MIX_DEFAULT_FREQUENCY , MIX_DEFAULT_FORMAT , 2 , 4096 ) == -1 ) throw Mix_GetError(); }

    inline const char* get_error()      { return SDL_GetError(); }

    inline void close_audio()           { Mix_CloseAudio(); }

}

#endif // SDLWRAP_H_INCLUDED
