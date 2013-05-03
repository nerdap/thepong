
#include "game.h"
#include "constants.h"

const int SCREEN_WIDTH      = 800;
const int SCREEN_HEIGHT     = 600;
const int SCREEN_BPP        = 32;
const int FRAMES_PER_SECOND = 80;

const int PADDLE_X_DISP     = 20;

const sdl::Point ORIGIN( 0 , 0 );
const sdl::Point PLAYER_SCORE_POS( 200 , 20 );
const sdl::Point AI_SCORE_POS( 600 , 20 );
const sdl::Point SCORE_TEXT_POS( 20 , 20 );     //  where the "score:" text is to be shown


Game::Game() : screen( sdl::set_video( SCREEN_WIDTH , SCREEN_HEIGHT , SCREEN_BPP , SDL_HWSURFACE | SDL_DOUBLEBUF ) ) ,
               player( PADDLE_X_DISP ) , computer( SCREEN_WIDTH - PADDLE_X_DISP - PADDLE_WIDTH ),
               player_score( 0 ) , ai_score( 0 )
{

    SDL_WM_SetCaption( "The Pong Project" , NULL );

    SDL_ShowCursor( 0 );

    sdl::open_audio();

    background.load( "background.png" );

    text.load( "vera.ttf" , 24 );
    text.set_color( sdl::Color( 0 , 255 , 0 ) );

    blip_sound = sound_man.load_sound( "sounds/blip.wav" );         //  the sound made when the paddle touches the ball
    lose_sound = sound_man.load_sound( "sounds/lose_point.wav" );   //  the sound made when the ball goes out of the play area

    player.load();
    computer.load();
    ball.load();

    welcome_screen();

    play();

}

void Game::play()
{
    bool launched = false;      //  is the ball moving

    bool quit = false;
    while( !quit )
    {

//          Event handling

        while( event.poll() )
        {
            if( event.type() == SDL_QUIT )
                quit = true;

            else if( event.type() == SDL_KEYDOWN )
            {
                switch( event.key() )
                {
                    case SDLK_ESCAPE :
                        quit = true;
                        break;

                    case SDLK_SPACE :
                    case SDLK_RETURN :
                        if( !launched )
                        {
                            launched = true;
                            ball.begin_moving();
                        }
                        break;

                    default : break;
                }

            }

            else if( event.type() == SDL_MOUSEBUTTONDOWN && !launched )
            {
                launched = true;
                ball.begin_moving();
            }

            player.handle_events( event );

        }


//          Logic

        if( launched )      //  only move the paddles if the game has started
        {
            ArtificialIntelligence::ai.move_paddle( computer , ball.pos );

            computer.move();
            ball.move();

            if( ball.handle_collision( sdl::Rect( PADDLE_X_DISP , player.y , PADDLE_WIDTH , PADDLE_HEIGHT ) ) ||
                ball.handle_collision( sdl::Rect( SCREEN_WIDTH - PADDLE_X_DISP - PADDLE_WIDTH , computer.y , PADDLE_WIDTH , PADDLE_HEIGHT ) ) )
            {
                sound_man.play( blip_sound );
            }
        }

        if( ball.pos.x < PADDLE_X_DISP )
        {
            ai_score++;
            ball.reset_pos();
            launched = false;
            sound_man.play( lose_sound );
        }

        else if( ball.pos.x > SCREEN_WIDTH - PADDLE_WIDTH - PADDLE_X_DISP )
        {
            player_score++;
            ball.reset_pos();
            launched = false;
            sound_man.play( lose_sound );
        }

        if( ai_score == MAX_SCORE || player_score == MAX_SCORE )
        {
            end_screen();
            return;
        }

//          Rendering

        screen.blit( ORIGIN , background );
        player.show();
        computer.show();
        ball.show();
        draw_scores();

        screen.flip();

//          Capping

        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
            SDL_Delay( 1000 / FRAMES_PER_SECOND - fps.get_ticks() );

    }

}

void Game::draw_scores()
{
    static std::stringstream ss( "" );

    text.blended( SCORE_TEXT_POS , "Score : " , screen );

    ss.str( "" );
    ss << player_score;
    text.blended( PLAYER_SCORE_POS , ss.str().c_str() , screen );

    ss.str( "" );
    ss << ai_score;
    text.blended( AI_SCORE_POS , ss.str().c_str() , screen );
}

void Game::welcome_screen()
{
    screen.clear( sdl::Color( 0 , 0 , 0 ) );

    std::string welcome_text = "Welcome to The Pong";
    sdl::Point  text_pos( SCREEN_WIDTH / 2 - text.size( welcome_text.c_str() ).getx() / 2 , SCREEN_HEIGHT / 2 - 48 );

    text.blended( text_pos , welcome_text.c_str() , screen );

    welcome_text = "Press any key to continue";
    text_pos.y += 32;
    text_pos.x = ( SCREEN_WIDTH - text.size( welcome_text.c_str() ).getx() ) / 2;

    SDL_Delay( 500 );
    text.blended( text_pos , welcome_text.c_str() , screen );

    screen.flip();

    while( true )
    {
        event.wait();
        if( event.type() == SDL_KEYDOWN || event.type() == SDL_MOUSEBUTTONDOWN )
            break;

        if( event.type() == SDL_QUIT )
            throw "";
    }
}

void Game::end_screen()
{
    screen.clear( sdl::Color( 0 , 0 , 0 ) );

    std::string end_message1;
    std::string end_message2;

    if( player_score == MAX_SCORE )
    {
        end_message1 = "Congratulations!";
        end_message2 = "You win!";
    }

    else if( ai_score == MAX_SCORE )
    {
        end_message1 = "Too bad.";
        end_message2 = "You lose.";
    }

    sdl::Point  text_pos( ( SCREEN_WIDTH - text.size( end_message1.c_str() ).getx() ) / 2 , SCREEN_HEIGHT / 2 - 48 );

    text.blended( text_pos , end_message1.c_str() , screen );

    text_pos.x = ( SCREEN_WIDTH - text.size( end_message2.c_str() ).getx() ) / 2;
    text_pos.y += 32;

    text.blended( text_pos , end_message2.c_str() , screen );

    screen.flip();

    while( true )
    {
        event.wait();

        if( event.type() == SDL_QUIT )
            return;

        else if( event.type() == SDL_KEYDOWN )
            if( event.key() == SDLK_ESCAPE )
                return;
    }

}

Game::~Game()
{
    text.free();
    background.free();
    sdl::close_audio();
}
