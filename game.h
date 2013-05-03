#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "sdl.h"
#include "timer.h"
#include "paddle.h"
#include "ball.h"
#include "ai.h"

#include <sstream>

class Game
{

private:

    static const int MAX_SCORE          = 10;

    sdl::Surface        screen;
    sdl::Event          event;

    sdl::Surface        background;

    sdl::Text           text;

    sdl::SoundManager   sound_man;

    PlayerPaddle        player;
    Paddle              computer;
    Ball                ball;

    Timer               fps;

    int                 player_score;
    int                 ai_score;

    unsigned int        blip_sound;
    unsigned int        lose_sound;

public:

     Game();
    ~Game();

    void play();
    void draw_scores();
    void welcome_screen();
    void end_screen();

};

#endif // GAME_H_INCLUDED
