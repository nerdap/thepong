#ifndef POINTRECTCOLOR_H_INCLUDED
#define POINTRECTCOLOR_H_INCLUDED

#include "sdlwrap.h"
#include <cmath>

//  This class abstracts an SDL_Color object

class sdl::Color
{

private:

//  Variables

    SDL_Color color;                            //  The SDL_Color that is abstracted

public:

//  Constructors

    Color() { color.r = 0; color.g = 0; color.b = 0; }

    Color(Uint8 r,Uint8 g,Uint8 b) { color.r = r; color.g = g; color.b = b; }

    Color(const SDL_Color& col): color(col) {}

//  Inline functions

    SDL_Color sdl() const { return color; }       //  Gets the SDL_Color

    Uint8& r()   {  return color.r; }
    Uint8& g()   {  return color.g; }
    Uint8& b()   {  return color.b; }

    Uint8  getr() const { return color.r; }
    Uint8  getg() const { return color.g; }
    Uint8  getb() const { return color.b; }

    void set(Uint8 r,Uint8 g,Uint8 b) { color.r = r; color.g = g; color.b = b; }

    Color& operator++ ()    { color.r++; color.g++; color.b++; return *this; }
    Color& operator++ (int) { color.r++; color.g++; color.b++; return *this; }

    Color& operator-- ()    { color.r--; color.g--; color.b--; return *this; }
    Color& operator-- (int) { color.r--; color.g--; color.b--; return *this; }

};


//  This class encapsulates an (x,y) coordinate for help in 2d game development

class sdl::Point
{

public:

//  Variables

    int x;
    int y;

//  Constructors

    Point(): x(0) , y(0) {}

    Point(int px,int py): x(px) , y(py) {}

//  Inline functions

    int getx() const { return x; }
    int gety() const { return y; }

    void set(int px,int py) { x = px; y = py; }

    int dist(const Point& pt) { return  static_cast<int>( std::sqrt( pow( x-pt.getx() , 2 ) + pow( y-pt.gety() , 2 ) ) ); }    //  The distance formula

    //  Operators

    sdl::Point operator+ (const sdl::Point& pt) { return sdl::Point( x + pt.getx() , y + pt.gety() ); }

    sdl::Point operator+= (const sdl::Point& pt) { *this = *this + pt; return *this; }

};

class sdl::Rect
{

private:

//  Variables

    SDL_Rect rect;

public:

//  Constructors

    Rect() { rect.x = rect.y = rect.w = rect.h = 0; }

    Rect(int x,int y,int w,int h) { rect.x = x; rect.y = y; rect.w = w; rect.h = h; }

    Rect(SDL_Rect r): rect(r) {}

//  Inline functions

    SDL_Rect sdl() const { return rect; }

    Sint16& x() { return rect.x; }
    Sint16& y() { return rect.y; }
    Uint16& w() { return rect.w; }
    Uint16& h() { return rect.h; }

    int getx() const { return rect.x; }
    int gety() const { return rect.y; }
    int getw() const { return rect.w; }
    int geth() const { return rect.h; }

    void set(int x,int y,int w,int h) { rect.x = x; rect.y = y; rect.w = w; rect.h = h; }

    bool in(sdl::Point pt) const { if( (pt.x > rect.x) && (pt.x < rect.x + rect.w) && (pt.y > rect.y) && (pt.y < rect.y + rect.h) ) return true; return false; }

    int left()   const      { return rect.x; }
    int right()  const      { return rect.x + rect.w; }
    int top()    const      { return rect.y; }
    int bottom() const      { return rect.y + rect.h; }

    bool operator== (const Rect& r) const { return ( (getx() == r.getx()) && (gety() == r.gety()) && (getw() == r.getw()) && (geth() == r.geth()) ); }
    bool operator!= (const Rect& r) const { return !( *this == r ); }
};

#endif // POINTRECTCOLOR_H_INCLUDED
