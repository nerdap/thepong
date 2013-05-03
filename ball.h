#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "sdl.h"
#include "constants.h"

class Ball
{

private:

public:

    static const int VELOCITY_Y = 3;
    static const int VELOCITY_X_MODIFIER = 30;

    sdl::Point       pos;

    sdl::Point       vel;

    sdl::Surface     image;

    void load();
    void begin_moving();
    void move();
    bool handle_collision( const sdl::Rect& );
    void show();
    void reset_pos();   //  sets the position of the ball back to the center of the screen

    ~Ball();



};

#endif // BALL_H_INCLUDED
