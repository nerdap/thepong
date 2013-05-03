#include "sdlwrap.h"
#include "pointrectcolor.h"
#include "surface.h"

SDL_Surface* sdl::set_video(Uint16 w,Uint16 h,Uint8 bpp,Uint32 flags)
{
    SDL_Surface* temp = SDL_SetVideoMode( w , h , bpp , flags );

    if( temp == NULL )
        throw SDL_GetError();

    return temp;
}

void sdl::draw_line(const sdl::Point& pt1,const sdl::Point& pt2,const sdl::Color& color,sdl::Surface& surf)
{
    int dx = pt1.getx() - pt2.getx();
    int dy = pt1.gety() - pt2.gety();

    if( dx == 0 && dy == 0 )
    {
        surf.set_pixel( pt1 , color );
        return;
    }

    if( abs(dx) > abs(dy) )
    {
        int xmin;
        int xmax;

        if( pt1.getx() < pt2.getx() )
        {
            xmin = pt1.getx();
            xmax = pt2.getx();
        }

        else
        {
            xmin = pt2.getx();
            xmax = pt1.getx();
        }

        float slope = dy/dx;

        for( int x = xmin; x < xmax; x++ )
        {
            int y = pt1.gety() + ( x - pt1.getx() ) * static_cast<int>( slope );
            surf.set_pixel( x , y , color );
        }
    }

    else
    {
        int ymin;
        int ymax;

        if( pt1.gety() < pt2.gety() )
        {
            ymin = pt1.gety();
            ymax = pt2.gety();
        }

        else
        {
            ymin = pt2.gety();
            ymax = pt1.gety();
        }

        float slope = dx/dy;

        for( int y = ymin; y < ymax; y++ )
        {
            int x = pt1.getx() + (y - pt1.gety() ) * static_cast<int>( slope );
            surf.set_pixel( x , y , color );
        }

    }

}

bool sdl::check_collision(const sdl::Rect& a,const sdl::Rect& b)
{
    if( a.gety() + a.geth() <= b.gety() )
        return false;

    if( a.gety() >= b.gety() + b.geth() )
        return false;

    if( a.getx() + a.getw() <= b.getx() )
        return false;

    if( a.getx() >= b.getx() + b.getw() )
        return false;

    return true;
}
