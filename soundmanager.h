#ifndef SOUNDMANAGER_H_INCLUDED
#define SOUNDMANAGER_H_INCLUDED

#include <vector>
#include <boost/foreach.hpp>
#include <SDL_mixer.h>
#include "sdlwrap.h"

class sdl::SoundManager
{

private:

    std::vector<Mix_Chunk*> sounds;

public:

    unsigned int load_sound( const char* );

    void play( unsigned int );

    void free();

    ~SoundManager() { free(); }
};

#endif // SOUNDMANAGER_H_INCLUDED
