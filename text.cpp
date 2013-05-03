#include "text.h"

using sdl::Text;

void Text::load(const char* fname,int tsize)
{
    if( !TTF_WasInit() )
        if( TTF_Init() == -1 )
            throw TTF_GetError();

    if( font != NULL)
        TTF_CloseFont( font );

    TTF_Font* lfont = TTF_OpenFont( fname , tsize );

    if( lfont == NULL )
        throw TTF_GetError();

    font = lfont;
}

void Text::solid(const sdl::Point& pt,const char* str,sdl::Surface& surf)
{
    sdl::Surface text = TTF_RenderText_Solid(font,str,tcolor.sdl());

    if( text.sdl() == NULL )
        throw TTF_GetError();

    surf.blit( pt , text );
}

void Text::shaded(const sdl::Point& pt,const char* str,const sdl::Color& bcol,sdl::Surface& surf)
{
    sdl::Surface text = TTF_RenderText_Shaded(font,str,tcolor.sdl(),bcol.sdl());

    if( text.sdl() == NULL )
        throw TTF_GetError();

    surf.blit( pt , text );
}

void Text::blended(const sdl::Point& pt,const char* str,sdl::Surface& surf)
{
    sdl::Surface text = TTF_RenderText_Blended(font,str,tcolor.sdl());

    if( text.sdl() == NULL )
        throw TTF_GetError();

    surf.blit( pt , text );
}

sdl::Point Text::size(const char* text)
{
    int w,h;

    if( TTF_SizeText( font , text, &w , &h ) == -1 )
        throw TTF_GetError();

    return sdl::Point( w , h );
}
