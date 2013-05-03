#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "sdlwrap.h"
#include "surface.h"
#include "pointrectcolor.h"


class sdl::Text
{

private:

//      Variables

    TTF_Font*   font;
    sdl::Color  tcolor;


public:

//      Constructors and destructors

    Text(): font( NULL ) , tcolor( sdl::Color(0,0,0) ) {}

    Text(TTF_Font* f,sdl::Color tc): font( f ) , tcolor( tc ) {}

//      Functions

    void load(const char*,int);

    void solid(const sdl::Point&,const char*,sdl::Surface&);

    void shaded(const sdl::Point&,const char*,const sdl::Color&,sdl::Surface&);

    void blended(const sdl::Point&,const char*,sdl::Surface&);

    sdl::Point size(const char*);

//      Inline Functions

    void set_color(const sdl::Color& col) { tcolor = col; }

    void set_font(TTF_Font* f)            { font = f; }

    void free()                           { if( font != NULL ) TTF_CloseFont( font ); }

    TTF_Font* get_font()                  { return font; }

};


#endif // TEXT_H_INCLUDED
