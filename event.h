#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

/*

Possibly unnecessary, however since
I've implemented it anyway, I might as well use it :P

*/


#include "sdlwrap.h"
#include "pointrectcolor.h"

class sdl::Event
{

private:

//      Variables

    SDL_Event event;

public:

//      Functions

    char get_ascii() const;

//      Inline functions

    bool poll()             { return static_cast<bool>( SDL_PollEvent( &event ) ); }

    void wait()             { if( !SDL_WaitEvent( &event ) ) throw SDL_GetError(); }

    SDL_Event sdl() const   { return event; }

    void push()             { if( SDL_PushEvent( &event ) == -1 ) throw SDL_GetError(); }

    Uint8 type() const      { return event.type; }

    SDLKey key() const      { return event.key.keysym.sym; }

//      Static functions

    static void pump() { SDL_PumpEvents(); }

    static Uint8* get_keystate(int* numkeys = NULL )   { return SDL_GetKeyState(numkeys); }

    static SDLMod get_modstate()                { return SDL_GetModState(); }

    static void unicode(bool on_off)            { SDL_EnableUNICODE( static_cast<int>( on_off ) ); }

    static bool unicode()                       { return static_cast<bool>( SDL_EnableUNICODE( -1 ) ); }

    static sdl::Point get_mousepos()            { sdl::Point temp; SDL_GetMouseState( &temp.x , &temp.y ); return temp; }

    static Uint8 get_mousestate(sdl::Point& pt) { return SDL_GetMouseState( &pt.x , &pt.y ); }

    static Uint8 get_mousestate()               { return SDL_GetMouseState( NULL , NULL ); }

    static Uint8 get_appstate()                 { return SDL_GetAppState(); }

    static sdl::Point get_relmousepos()         { sdl::Point temp; SDL_GetRelativeMouseState( &temp.x , &temp.y ); return temp; }


};

#endif // EVENT_H_INCLUDED
