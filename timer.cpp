#include "timer.h"

void Timer::start()
{
    _started = true;
    _paused  = false;

    _startticks = SDL_GetTicks();
}

void Timer::stop()
{
    _started = _paused = false;
}

void Timer::pause()
{
    if( _paused || !_started )                                        //If the timer is already paused or the timer has been stopped, return
        return;

    _paused = true;

    _pausedticks = SDL_GetTicks() - _startticks;
}

void Timer::resume()
{
    if( !_paused || !_started )
        return;

    _paused = false;

    _startticks = SDL_GetTicks() - _pausedticks;

    _pausedticks = 0;
}

Uint32 Timer::get_ticks()
{
    if( !_started )
        return 0;

    if( _paused )
        return _pausedticks;

    return SDL_GetTicks() - _startticks;
}

bool Timer::paused()
{
    return _paused;
}

bool Timer::started()
{
    return _started;
}
