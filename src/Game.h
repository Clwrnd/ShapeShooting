#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include <SFML/Graphics.hpp>

struct PlayerConfig
{
    int SR, CR, FR, FG, FB, OR, OG, OB, OT, V,MR,MG,MB,MOR,MOG,MOB;
    float S;
};
struct EnnemyConfig
{
    int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI ,SMIN, SMAX;
};
struct BulletConfig
{
    int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L;
    float S;
};

class Game
{
    sf::RenderWindow window;
    EntityManager Mentities;
    sf::Font font;
    sf::Text score_text;
    PlayerConfig player_config;
    EnnemyConfig ennemy_config;
    BulletConfig bullet_config;
    int score = 0;
    int current_frame = 0;
    int lastTimeEnemySpwanded = 0;
    int lastTimeSpecSpwanded =0 ;
    bool paused = false;
    bool running = true;

    std::shared_ptr<Entity> player;

    void init(const std::string &config);
    void setPaused();

    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender();
    void sEnemySpawner();
    void sCollision();

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spwanBullet(std::shared_ptr<Entity> entity, const Vec2 &mousePos);
    void spwanSpecWeapon(std::shared_ptr<Entity>,const Vec2 &mousePos);

public:
    Game(const std::string  & config);

    void run();
};
