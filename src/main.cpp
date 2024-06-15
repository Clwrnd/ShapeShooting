#include <SFML/Graphics.hpp>
#include "Vec2.h"
#include<iostream>
#include <string>

int main()
{
    Vec2 s(721,-134);
    Vec2 q(143.92,2.21);

    std::cout << "test";
    std::cout << s.dist(q) ;
}
