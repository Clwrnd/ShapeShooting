#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include <SFML/Graphics.hpp>

struct PlayerConfig {int SR,CR,FR,FG,FB,OR,OG,OB,OT,V;float S;};
struct EnnemyConfig {int SR,CR,OR,OG,OB,OT,VMIN,VMAX,L,SI;float SMIN,SMAX;};
struct BulletConfig {int SR,CR,FR,FG,FB,OR,OG,OB,OT,V,L;float S;  };

class Game
{
    sf::RenderWindow window;

public:

    Game( ); 

    void run();


};


