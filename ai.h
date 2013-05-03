#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "paddle.h"
#include "pointrectcolor.h"
#include "constants.h"

class ArtificialIntelligence
{

public:

    static ArtificialIntelligence ai;

    void move_paddle( Paddle& , const sdl::Point& );

};

#endif // AI_H_INCLUDED
