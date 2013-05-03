
#include "paddle.h"

const int PADDLE_WIDTH  = 16;
const int PADDLE_HEIGHT = 128;

sdl::Surface Paddle::image;

void Paddle::load()
{
    y = ( SCREEN_HEIGHT - PADDLE_HEIGHT ) / 2;

    if( !image )
        image.load_transparent( "paddle.png" );

}

//  mouse based movement is much better
void PlayerPaddle::handle_events(const sdl::Event& event)
{
    if( event.type() == SDL_MOUSEMOTION )
        y = sdl::Event::get_mousepos().gety();

    if( y < 0 )
        y = 0;

    else if( y + PADDLE_HEIGHT > SCREEN_HEIGHT )
        y= SCREEN_HEIGHT - PADDLE_HEIGHT;
}

void Paddle::move()
{

    switch( direction )
    {
        case UP :
            y -= VELOCITY;
            break;

        case DOWN :
            y += VELOCITY;
            break;

        default : break;
    }

//  x-direction is not handled since the paddle cannot move in that direction

    if( y < 0 )          //     Make sure the paddle is within the bounds of the screen
        y = 0;

    else if( y + PADDLE_HEIGHT > SCREEN_HEIGHT )
        y = SCREEN_HEIGHT - PADDLE_HEIGHT;
}

void Paddle::show()
{
    sdl::Surface( SDL_GetVideoSurface() ).blit( sdl::Point( PADDLE_X_DISP , y ) , image );
}

Paddle::~Paddle()
{
    image.free();
}
