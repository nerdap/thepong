
#include "ai.h"

ArtificialIntelligence ArtificialIntelligence::ai;

void ArtificialIntelligence::move_paddle( Paddle& paddle , const sdl::Point& ball_pos )
{
    if( paddle.y + PADDLE_HEIGHT / 2 > ball_pos.gety() )
        paddle.direction = Paddle::UP;

    else if( paddle.y + PADDLE_HEIGHT / 2 < ball_pos.gety() )
        paddle.direction = Paddle::DOWN;
}
