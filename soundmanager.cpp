#include "soundmanager.h"

using sdl::SoundManager;

unsigned int SoundManager::load_sound( const char* filename )
{
    Mix_Chunk* temp = Mix_LoadWAV( filename );

    if( temp == NULL )
        throw Mix_GetError();

    sounds.push_back( temp );

    return sounds.size() - 1;
}

void SoundManager::play( unsigned int id )
{
    if( id >= sounds.size() || sounds.at( id ) == NULL )
        throw "SoundManager::play() : requested sound does not exist.";

    if( Mix_PlayChannel( -1 , sounds.at( id ) , 0 ) == -1 )
        throw Mix_GetError();


}

void SoundManager::free()
{
    BOOST_FOREACH( Mix_Chunk* sound , sounds )
        Mix_FreeChunk( sound );

    sounds.clear();
}
