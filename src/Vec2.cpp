#include "Vec2.h"
#include <math.h>

Vec2::Vec2(){

};

Vec2::Vec2(float xin, float yin)
    : x(xin), y(yin){};

bool Vec2::operator==(const Vec2 &toComp) const
{
    return (x == toComp.x && y == toComp.y);
}

bool Vec2::operator!=(const Vec2 &toComp) const
{
    return !(x == toComp.x && y == toComp.y);
}

Vec2 Vec2::operator*(const float toMult) const
{
    return Vec2(x * toMult, y * toMult);
}

void Vec2::operator*=(const float toMult)
{
    x = x * toMult;
    y = y * toMult;
}

Vec2 Vec2::operator/(const float toDiv) const
{
    return Vec2(x / toDiv, y / toDiv);
}

void Vec2::operator/=(const float toDiv)
{
    x = x / toDiv;
    y = y / toDiv;
}

Vec2 Vec2::operator+(const Vec2 toAdd) const
{
    return Vec2(x + toAdd.x, y + toAdd.y);
}

void Vec2::operator+=(const Vec2 toAdd)
{
    x = x + toAdd.x;
    y = y + toAdd.y;
}

Vec2 Vec2::operator-(const Vec2 toSou) const
{
    return Vec2(x - toSou.x, y - toSou.y);
}

void Vec2::operator-=(const Vec2 toSou)
{
    x = x - toSou.x;
    y = y - toSou.y;
}

float Vec2::dist(const Vec2 &toComp) const
{
    return (std::sqrt((x - toComp.x) * (x - toComp.x) + (y - toComp.y) * (y - toComp.y)));
}