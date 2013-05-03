#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <SDL.h>

class Timer
{
private:

    Uint32              _startticks;
    Uint32              _pausedticks;
    bool                _paused;
    bool                _started;

public:

    Timer(): _startticks(0) , _pausedticks(0) , _paused(false) , _started(false) {}

    void start();
    void stop();
    void pause();
    void resume();

    Uint32 get_ticks();

    bool paused();
    bool started();


};

#endif // TIMER_H_INCLUDED
