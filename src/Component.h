#pragma once

#include "Vec2.h"
#include <SFML/Graphics.hpp>

class CTransform
{
public:
    Vec2 pos = {0, 0};
    Vec2 speed = {0, 0};
    float ang = 0;

    CTransform(const Vec2 &pos_in,const Vec2 &speed_in, float ang_in)
        : pos(pos_in), speed(speed_in), ang(ang_in)
    {
    }
};

class CShape
{
public:
    sf::CircleShape circle;
    CShape(float radius, int points, const sf::Color &fill,
           const sf::Color &outline, float thickness)
           : circle(radius,points)
    {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius, radius);
    }
};

class CCollision
{
public:
    float radius = 0;
    CCollision(float r)
        : radius(r)
    {
    }
};

class CScore
{
public:
    int score = 0;
    CScore(int s)
        : score(s)
    {
    }
};

class CLifespan
{
public:
    int remaining = 0;
    int total = 0;
    CLifespan(int rm, int tl)
        : remaining(rm), total(tl)
    {
    }
};

class CInput
{
public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;

    CInput() {}
};

class CDelayedeffect
{
public:
    int final_effect = 0;
    CDelayedeffect(int f_e) 
    : final_effect(f_e)
    {   
    };
};

class CWave
{
public:
    int radius = 0;
    CWave(int rad)
    : radius(rad)
    {

    };
};