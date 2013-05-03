#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

#include "sdl.h"
#include "constants.h"

class Paddle
{

public:

    enum Direction { NONE , UP , DOWN };

    static const int VELOCITY       = 2;

    const int    PADDLE_X_DISP;

    static sdl::Surface image;     //  image of the paddle, common to both the paddles

    int                 y;

    Direction           direction;


    Paddle( int paddle_x_disp ) : PADDLE_X_DISP( paddle_x_disp ) {}
    ~Paddle();

    void load();
    void move();
    void show();


};

class PlayerPaddle : public Paddle
{

public:

    PlayerPaddle( int paddle_x_disp ) : Paddle( paddle_x_disp ) {}

    void handle_events(const sdl::Event&);

};

#endif // PADDLE_H_INCLUDED
