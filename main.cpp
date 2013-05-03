
#include "game.h"

int main(int argc,char* argv[])
{

    try
    {
        sdl::init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
        Game game;
    }

    catch(const char* error)
    {
        fprintf( stderr , error );
        sdl::quitsdl();
        return 1;
    }

    sdl::quitsdl();

    return 0;

}
