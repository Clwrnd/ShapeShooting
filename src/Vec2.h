#pragma once

class Vec2
{
public:
    float x = 0;
    float y = 0;

    Vec2();
    Vec2(float xin, float yin);

    bool operator==(const Vec2 &toComp) const;
    bool operator!=(const Vec2 &toComp) const;

    Vec2 operator*(const float toMult) const;
    Vec2 operator/(const float toDiv) const;
    Vec2 operator+(const Vec2 toAdd) const;
    Vec2 operator-(const Vec2 toSou) const;

    void operator*=(const float toMult);
    void operator/=(const float toDiv);
    void operator+=(const Vec2 toAdd);
    void operator-=(const Vec2 toSou);

    float dist(const Vec2 &toComp) const;
};
