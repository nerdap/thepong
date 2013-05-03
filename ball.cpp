
#include "ball.h"
#include <cstdlib>
#include <ctime>
#include <ctime>

const int BALL_SIZE = 16;

void Ball::load()
{
    image.load_transparent( "ball.png" );

    pos.x = ( SCREEN_WIDTH - BALL_SIZE ) / 2;
    pos.y = ( SCREEN_HEIGHT - BALL_SIZE ) / 2;

    vel.set( 0 , 0 );

    std::srand( std::time( NULL ) );
}

void Ball::reset_pos()
{
    pos.x = ( SCREEN_WIDTH - BALL_SIZE ) / 2;
    pos.y = ( SCREEN_HEIGHT - BALL_SIZE ) / 2;
}

void Ball::begin_moving()
{
    unsigned int direction = std::rand() % 10000;   //  if the number is greater than 5,000 - move to the left, else, to the right
    vel.x = direction > 5000 ? -VELOCITY_Y : +VELOCITY_Y;

    //  do the same for the vertical direction

    direction = std::rand() % 10000;
    vel.y = direction > 5000 ? -VELOCITY_Y : +VELOCITY_Y;
}

void Ball::move()
{
    pos += vel;

    if( pos.y < 0 || pos.y + BALL_SIZE > SCREEN_HEIGHT )
        vel.y = -vel.y;
}

bool Ball::handle_collision( const sdl::Rect& paddle_rect )
{

    static sdl::Rect ball_rect;     //  to avoid construction and destruction repeatedly
    ball_rect.set( pos.x , pos.y , BALL_SIZE , BALL_SIZE );

    if( sdl::check_collision( paddle_rect , ball_rect ) )
    {

        //  x-velocity = - distance between the center of the paddle and the ball position / VELOCITY_X_MODIFIER

        if( paddle_rect.getx() == PADDLE_X_DISP )
        {
            vel.x = ( ( paddle_rect.top() + paddle_rect.bottom() ) / 2 ) / VELOCITY_X_MODIFIER;

            if( vel.x == 0 )    //  0 x-velocity is not nice
                vel.x = 1;
        }

        else
        {
            vel.x = -( ( paddle_rect.top() + paddle_rect.bottom() ) / 2 ) / VELOCITY_X_MODIFIER;

            if( vel.x == 0 )
                vel.x = -1;
        }

        //  y-velocity = VELOCITY_Y + relative yvel of the paddle

        if( paddle_rect.gety() + PADDLE_HEIGHT / 2 < pos.y )
            vel.y = +VELOCITY_Y;

        else
            vel.y = -VELOCITY_Y;

        return true;    //  a collision has occured
    }

    return false;

}

void Ball::show()
{
    sdl::Surface( SDL_GetVideoSurface() ).blit( pos , image );
}

Ball::~Ball()
{
    image.free();
}
